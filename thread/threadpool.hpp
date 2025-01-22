#include <thread>
#include <queue>
#include <mutex>
#include <functional>
#include <type_traits>
#include <future>

using namespace std;

class Thread_pool{
    std::queue<std::function<void()>> tasks_;
    std::vector<std::thread> threads_;
    int nums_;
    std::mutex queue_mutex_;
    std::condition_variable cv_;
    std::atomic<bool> stop_ = false;
public:
    Thread_pool(int num_threads){
        nums_ = num_threads;
        for (size_t i = 0; i < num_threads; ++i) {
            threads_.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex_);
                        this->cv_.wait(lock, [this] {
                            return this->stop_ ||!this->tasks_.empty();
                        });
                        if (this->stop_ && this->tasks_.empty()) {
                            return;
                        }
                        task = std::move(this->tasks_.front());
                        this->tasks_.pop();
                    }
                    task();
                }
            });
        }
    }
    ~Thread_pool(){
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            stop_ = true;
        }
        cv_.notify_all();
        for(std::thread& t : threads_){
            t.join();
        }
    }
    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result<std::remove_reference_t<F>, Args...>::type> {
        using return_type = typename std::invoke_result<std::remove_reference_t<F>, Args...>::type;
        // 修改 std::packaged_task 的签名
        auto task = std::make_shared<std::packaged_task<return_type(Args...)>>(std::forward<F>(f));
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            if (stop_) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            // 修改 Lambda 捕获列表，以传递参数
            tasks_.emplace([task, args = std::make_tuple(std::forward<Args>(args)...)]() mutable {
                std::apply(*task, args);
            });
        }
        cv_.notify_one();
        return res;
    }
};