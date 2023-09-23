#ifndef __WOLF_CURSOR__
#define __WOLF_CURSOR__

namespace Wolf {
namespace Cursor {

    /// @brief Modes that control cursor behaviour
    enum class CursorMode : unsigned long int {

        /// @brief Visible and not locked
        Normal,
        /// @brief Hides the cursor when on top of window
        Hidden,

        /// @brief Hides the cursor, and locks to the center of the window
        Disabled,

        /// @brief Locks the cursor in the center of the window
        Captured
    };
    void set_mode(CursorMode mode);
}
}

#endif