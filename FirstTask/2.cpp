#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <chrono>
#include <source_location>
#include <sstream>
#include <iomanip>

class Tracer {
private:
    std::string message_;
    std::chrono::time_point<std::chrono::system_clock> start_time_;
    std::source_location location_;
    std::vector<std::string> call_stack_;

    static std::string current_time() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        ss << "." << std::setfill('0') << std::setw(3) << ms.count();
        return ss.str();
    }

public:
    explicit Tracer(std::string  message,
                   const std::source_location& location = std::source_location::current())
        : message_(std::move(message)), location_(location) {
        start_time_ = std::chrono::system_clock::now();

        std::string stack_entry = "[" + current_time() + "] ENTER: " + message_ +
                                 " at " + location_.file_name() + ":" +
                                 std::to_string(location_.line());
        call_stack_.push_back(stack_entry);
        std::cout << stack_entry << '\n';
    }
    
    ~Tracer() {
        auto end_time = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time_);

        std::string stack_exit = "[" + current_time() + "] EXIT: " + message_ +
                                " (took " + std::to_string(duration.count()) + "ms)" +
                                " at " + location_.file_name() + ":" +
                                std::to_string(location_.line());
        std::cout << stack_exit << '\n';

        if (!call_stack_.empty()) {
            call_stack_.pop_back();
        }
    }

    void trace(const std::string& message,
                     const std::source_location& location = std::source_location::current()) {
        std::string msg = "[" + current_time() + "] " + message + " at " + location.file_name() + ":"
                              + std::to_string(location.line());
        std::cout << msg << '\n';
        call_stack_.push_back(msg);
    }

    void print_call_stack() const {
        std::cout << "\n=== CALL STACK ===" << '\n';
        if (call_stack_.empty()) {
            std::cout << "Call stack is empty" << '\n';
        } else {
            for (size_t i = 0; i < call_stack_.size(); ++i) {
                std::cout << "#" << i << " " << call_stack_[i] << '\n';
            }
        }
        std::cout << "==================\n" << '\n';
    }

    // For outer use
    static std::string get_current_time() {
        return current_time();
    }
};

void func() {
    Tracer tracer("Another function");
}

int main() {
    Tracer tracer("Main function");
    tracer.trace("Hello World");
    tracer.print_call_stack();
    func();

    return 0;
}
