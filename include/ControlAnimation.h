#pragma once
#include <vector>
#include <functional>
#include <raylib.h>


class ControlAnimation {
    public:
        ControlAnimation() :steps({}), currentStep(0), isPaused(false) {}
    
        // Thêm một bước vào danh sách các bước
        void AddStep(std::function<void()> step) {
            steps.push_back(step);
        }
    
        void ThisStep() {
            if(isPaused && currentStep < steps.size()) {
                steps[currentStep]();
            }
        }

        // Chạy bước tiếp theo
        void NextStep() {
            if (!isPaused && currentStep < steps.size()) {
                steps[currentStep]();
                currentStep++;
            }
        }
    
        // Quay lại bước trước
        void PreviousStep() {
            if (!isPaused && currentStep > 0) {
                currentStep--;
                steps[currentStep]();
            }
        }
    
        // Bật/tắt trạng thái pause
        void TogglePause() {
            isPaused = !isPaused;
        }
    
        // Kiểm tra xem animation có đang pause không
        bool IsPaused() const {
            return isPaused;
        }
    
        // Kiểm tra xem đã hoàn thành tất cả các bước chưa
        bool IsFinished() const {
            return currentStep >= steps.size();
        }
    
        // Đặt lại animation về trạng thái ban đầu
        void Reset() {
            currentStep = 0;
            isPaused = false;
            steps.clear();
        }
    
    //private:
        std::vector<std::function<void()>> steps; // Danh sách các bước
        size_t currentStep; // Bước hiện tại
        bool isPaused = false; // Trạng thái pause
    };