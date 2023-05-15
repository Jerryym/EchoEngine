# Event System

---

渲染引擎中的Event System是指一种事件驱动的机制，用于处理和响应渲染过程中的各种事件。一般常见得事件类型有：**窗口事件、鼠标和键盘的输入事件、Application操作事件**等。
在EchoEngine中，设计一个枚举类类型`enum class EventType`来表示引擎的Event System中存在事件类型：

``` C++
// 事件类型枚举类
enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,// 窗口操作
    AppTick, AppUpdate, AppRender,                                       // App操作
    KeyPressed, KeyReleased, KeyTyped,                                   // 键盘操作
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled   // 鼠标操作
};
```

从事件类型枚举类中，可以看出，引擎中的事件可以分为四个大类：

* 窗口事件
  * WindowClose:窗口关闭事件。
  * WindowResize:窗口大小调整事件。
  * WindowFocus:窗口获得焦点事件。
  * WindowLostFocus:窗口失去焦点事件。
  * WindowMoved:窗口位置移动事件。
* Application操作事件
  * AppTick:应用程序单次更新事件。
  * AppUpdate:应用程序多次更新事件。
  * AppRender:应用程序渲染事件。
* 键盘操作事件
  * KeyPressed:键盘按键按下事件。
  * KeyReleased:键盘按键释放事件。
  * KeyTyped:键盘按键输入事件。
* 鼠标操作事件
  * MouseButtonPressed:鼠标按键按下事件。
  * MouseButtonReleased:鼠标按键释放事件。
  * MouseMoved:鼠标位置移动事件。
  * MouseScrolled:鼠标滚动事件。

并设计一个事件过滤枚举类型`enum EventCategory`，用于精确处理各类事件类型，且使用了位运算符 `BIT()` 来表示该事件类型是否被选中：

> Note:使用位运算符可以方便地将多个事件类型组合起来，从而实现更细粒度的事件过滤。

``` C++
// 事件过滤枚举
enum EventCategory
{
    None = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput       = BIT(1),
    EventCategoryKeyboard    = BIT(2),
    EventCategoryMouse       = BIT(3),
    EventCategoryMouseButton = BIT(4)
};
```
