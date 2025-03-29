#include <vector>
#include <string>
#include "Variables.h"
#include "Graph.h"
using namespace std;


class GraphAlgorithm {
public:
    enum AlgorithmType {
        BFS,
        DFS,
        MINIMUM_SPANNING_TREE,
        // ... các thuật toán khác
    };

    enum StepType {
        // Các bước chung có thể áp dụng cho nhiều thuật toán
        START,
        INIT,
        SELECT_NODE,
        VISIT_NODE,
        EXPLORE_NEIGHBOUR,
        ADD_TO_STRUCTURE, // Ví dụ: thêm vào hàng đợi, ngăn xếp, tập cạnh
        END,
        // ... Các bước cụ thể cho từng thuật toán có thể được thêm vào lớp con
    };

    AlgorithmType currentAlgorithm;
    vector<string> pseudocode;
    int currentPseudocodeLine;
    bool isAnimating;
    float animationSpeed;
    int currentStepIndex; // Theo dõi bước hiện tại trong quá trình thực hiện thuật toán
    std::vector<std::vector<Drawable*>> animationQueue; // Queue chứa trạng thái đồ thị cho animation

    GraphAlgorithm(AlgorithmType type) : currentAlgorithm(type), isAnimating(false), animationSpeed(1.0f), currentStepIndex(0), currentPseudocodeLine(-1) {}

    virtual ~GraphAlgorithm() {}

    virtual void init(Graph* graph, Vertex* startNode = nullptr) = 0;
    virtual void step() = 0; // Thực hiện một bước của thuật toán và cập nhật animationQueue
    virtual void draw(Graph* graph) = 0;
    virtual void startAnimation() { isAnimating = true; currentStepIndex = 0; }
    virtual void stopAnimation() { isAnimating = false; }
    virtual void reset() {
        isAnimating = false;
        currentStepIndex = 0;
        currentPseudocodeLine = -1;
        animationQueue.clear();
    }

    void setPseudocode(const std::vector<std::string>& code) {
        pseudocode = code;
        currentPseudocodeLine = -1; // Reset dòng highlight
    }

    void highlightPseudocode(int line) {
        if (line >= 0 && line < pseudocode.size()) {
            currentPseudocodeLine = line;
        } else {
            currentPseudocodeLine = -1;
        }
    }

    // Các phương thức hỗ trợ chung khác có thể được thêm vào
};