#pragma once

/**
*   @brief canvas mode
*/
enum CanvasMode
{
    Select_Mode,                                ///< canvas select mode
    Line_Mode,                                  ///< canvas line mode
};

/**
*   @brief line state
*/
enum LineState
{
    Line_Initial_State,                           ///< line with none point 
    Line_Need_Select_From_State,                  ///< line with none point 
    Line_Need_Select_To_State,                    ///< line with from point 
};

/**
*  @brief select state
*/
enum SelectState
{
    Select_Initial_State,                         ///< select nothing
    Select_Line_State,                            ///< select line
    Select_Prepare_Drag_State,                    ///< prepare to drag line
    Select_Draging_State,                         ///< dragging line
};

/**
*  @brief the state of component
*/
enum ComponentState
{
    Component_Normal_State,                        ///< normal state. not run
    Component_Calculate_State,                     ///< calculate state. running
    Component_Finished_State,                      ///< finished state. run finished
};

/**
*  @brief canvas state
*/
struct State
{
    /**
     * @brief     canvas mode
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 16:31
     */
    CanvasMode mode;
    /**
     * @brief     line state
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 16:31
     */
    LineState lineState;
    /**
     * @brief     select state
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 16:31
     */
    SelectState selectState;
};

/**
 * @brief     graphic item port type. one graphic item has one input port one output port
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-31 10:33
 */
enum PortType
{
    /**
     * @brief     input type port
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-8-31 10:33
     */
    Port_Type_Input,
    /**
     * @brief     output type port
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-8-31 10:33
     */
    Port_Type_Output,
};

/**
 * @brief     Graphics Item 's Port State
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-3 16:41
 */
enum PortState
{
    /**
     * @brief     Port State Normal. In Line Mode Means Cursor pos is far away
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 16:41
     */
    Port_State_Normal,
    /**
     * @brief     Port State Nearby. In Line Mode Means Cursor pos is near and less than the judgment distance
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 16:43
     */
    Port_State_Nearby,
    /**
     * @brief     Port State Selected. In Line Mode Means This Port is Selected As From or To Port of Line
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 16:45
     */
    Port_State_Selected,
    /**
     * @brief     Port State Already Selected. And Cursor is Nearby. Also Can Select As Another Line 's Port
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 16:46
     */
    Port_State_Selected_Nearby,
};

enum LineType
{
    /**
     * @brief     Z Turning Type.
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 8:51
     */
    Line_ZTurning_Type,

    /**
     * @brief     Z Center Type.
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 8:53
     */
    Line_ZCenter_Type,

    /**
     * @brief     S Turning Type.
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 9:00
     */
    Line_STurning_Type,

    /**
     * @brief     S Center Type
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 9:18
     */
    Line_SCenter_Type,

    /**
     * @brief     O Clock Type
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 9:18
     */
    Line_OClock_Type,
};

typedef enum LineType IndicateLineType;

/**
 * @brief     Direction Define.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-2 14:40
 */
enum Direction
{
    /**
     * @brief     Up Direction.
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 14:41
     */
    Up,
    /**
     * @brief     Down Direction
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 14:41
     */
    Down,
    /**
     * @brief     Left Direction
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 14:41
     */
    Left,
    /**
     * @brief     Right Direction
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 14:42
     */
    Right,
};

/**
 * @brief     Notify State Enum
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-3 16:39
 */
enum NotifyState
{
    /**
     * @brief     Normal. No Notify
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 16:40
     */
    Notify_Noraml,
    /**
     * @brief     Warning. Warning Notify
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 16:40
     */
    Notify_Warning,
    /**
     * @brief     Error. Error Notify
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 16:40
     */
    Notify_Error,
};