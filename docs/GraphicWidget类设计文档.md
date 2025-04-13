# **GraphicWidget类设计文档**

## 版本信息

- **版本号**: v1.0
- **创建日期**: 2024-12-17
- **作者**: Jerry
- **修改记录**:

  | 修改日期   | 修改人       | 修改内容                 | 版本号 |
  | ---------- | ------------ | ------------------------ | ------ |
  | 2024-12-17 | Jerry | 编写GraphicWidget类设计文档 | v1.0   |

---

## 1. 类概要

- **类名**: GraphicWidget
- **模块/组件**: EchoEditor->GUI
  - **描述**: 该类用于EchoEditor中显示图形的组件。

---

## 2. 设计目标

- 提供图形显示功能

---

## 3. 类关系

- **依赖关系**:
  - 该类依赖`QWidget`和`QTimer`模块。
- **继承关系**:
  - 该类继承`QWidget`。
- **关联关系**:
  - 该类内部使用`QTimer`对象来控制界面刷新。

---

## 4. 类的接口设计

### 4.1 公共接口（Public Methods）

| 方法名     | 参数           | 返回值     | 描述             |
| ---------- | -------------- | ---------- | ---------------- |
| `GraphicWidget` | uint32_t nWidth, uint32_t nHeight, QWidget* parent | 无 | 构造函数 |
| `~GraphicWidget` | 无 | 无 | 析构函数 |
| `paintEvent` | QPaintEvent* event | 无 | 绘制事件处理函数 |

### 4.2 成员变量（Attributes）

| 名称       | 类型 | 访问级别    | 描述               |
| ---------- | ---- | ----------- | ------------------ |
| `m_pTimer` | QTimer* | `private` | 定时器对象，用于刷新界面 |

---

## 5. 设计详细说明

- **主要逻辑**
  - 在构造函数中，初始化图形显示组件的大小，并设置帧率为60Hz。
  - 使用`QTimer`对象`m_pTimer`来定时触发`update`函数，从而刷新界面。
  - paintEvent 函数用于处理绘制事件

---

## 6. 示例代码

```cpp
// GraphicWidget.h
#pragma once
#include <QWidget>
#include <QTimer>

namespace EchoEditor {

    class GraphicWidget : public QWidget {
        Q_OBJECT
    public:
        GraphicWidget(uint32_t nWidth, uint32_t nHeight, QWidget* parent = nullptr);
        virtual ~GraphicWidget();

    public:
        virtual void paintEvent(QPaintEvent* event) override;

    private:
        QTimer* m_pTimer = nullptr;  // 定时器：用于刷新界面
    };

}

// GraphicWidget.cpp
#include "pch.h"
#include "GraphicWidget.h"

namespace EchoEditor {

    GraphicWidget::GraphicWidget(uint32_t nWidth, uint32_t nHeight, QWidget* parent)
        : QWidget(parent) {
        resize((int)nWidth, (int)nHeight);

        // 设置帧率为60
        m_pTimer = new QTimer(this);
        connect(m_pTimer, &QTimer::timeout, this, QOverload<>::of(&GraphicWidget::update));
        m_pTimer->start(1000 / 60.0);
    }

    GraphicWidget::~GraphicWidget() {
        if (m_pTimer != nullptr) {
            delete m_pTimer;
            m_pTimer = nullptr;
        }
    }

    void GraphicWidget::paintEvent(QPaintEvent* event) {
        // 绘制逻辑
    }

}
```
