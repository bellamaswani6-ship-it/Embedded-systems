#include <iostream>
#include <list>
#include <string>

class TextEditor {
private:
    std::list<std::string> history;   // Stores performed actions
    std::list<std::string> redoStack; // Stores undone actions for redo

public:
    // Perform an action
    void performAction(const std::string& action) {
        history.push_back(action); // Add action to history
        redoStack.clear();         // Clear redo stack (since new action is performed)
        std::cout << "Performed: " << action << "\n";
    }

    // Undo last action
    void undo() {
        if (history.empty()) {
            std::cout << "Nothing to undo!\n";
            return;
        }
        std::string lastAction = history.back();
        history.pop_back();
        redoStack.push_back(lastAction); // Move action to redo stack
        std::cout << "Undo: " << lastAction << "\n";
    }

    // Redo last undone action
    void redo() {
        if (redoStack.empty()) {
            std::cout << "Nothing to redo!\n";
            return;
        }
        std::string lastUndo = redoStack.back();
        redoStack.pop_back();
        history.push_back(lastUndo); // Move action back to history
        std::cout << "Redo: " << lastUndo << "\n";
    }

    // Display history of actions
    void showHistory() {
        std::cout << "Action History: ";
        for (const auto& action : history)
            std::cout << action << " -> ";
        std::cout << "END\n";
    }
};

int main() {
    TextEditor editor;

    // Performing actions
    editor.performAction("Typed 'Hello'");
    // editor.performAction("Bolded 'Hello'");
    // editor.performAction("Inserted 'World'");

    editor.showHistory();

    // // Undo operations
     editor.undo();
    editor.undo();
    
    // // Redo operation
    editor.redo();

    // editor.showHistory();

    return 0;
}

