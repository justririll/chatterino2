#pragma once

#include "common/ChatterinoSetting.hpp"
#include "common/Singleton.hpp"
#include "util/RapidJsonSerializeQString.hpp"

#include <pajlada/settings/setting.hpp>
#include <QBrush>
#include <QColor>

namespace chatterino {

class WindowManager;

class Theme final : public Singleton
{
public:
    Theme();

    bool isLightTheme() const;

    struct TabColors {
        QColor text;
        struct {
            QBrush regular;
            QBrush hover;
            QBrush unfocused;
        } backgrounds;
        struct {
            QColor regular;
            QColor hover;
            QColor unfocused;
        } line;
    };

    QColor accent{"#00aeef"};

    /// WINDOW
    struct {
        QColor background;
        QColor text;
        QColor borderUnfocused;
        QColor borderFocused;
    } window;

    /// TABS
    struct {
        TabColors regular;
        TabColors newMessage;
        TabColors highlighted;
        TabColors selected;
        QColor border;
        QColor dividerLine;
    } tabs;

    /// MESSAGES
    struct {
        struct {
            QColor regular;
            QColor caret;
            QColor link;
            QColor system;
            QColor chatPlaceholder;
        } textColors;

        struct {
            QColor regular;
            QColor alternate;
            // QColor whisper;
        } backgrounds;

        QColor disabled;
        //        QColor seperator;
        //        QColor seperatorInner;
        QColor selection;

        QColor highlightAnimationStart;
        QColor highlightAnimationEnd;
    } messages;

    /// SCROLLBAR
    struct {
        QColor background;
        QColor thumb;
        QColor thumbSelected;
        struct {
            QColor highlight;
            QColor subscription;
        } highlights;
    } scrollbars;

    /// TOOLTIP
    struct {
        QColor text;
        QColor background;
    } tooltip;

    /// SPLITS
    struct {
        QColor messageSeperator;
        QColor background;
        QColor dropPreview;
        QColor dropPreviewBorder;
        QColor dropTargetRect;
        QColor dropTargetRectBorder;
        QColor resizeHandle;
        QColor resizeHandleBackground;

        struct {
            QColor border;
            QColor focusedBorder;
            QColor background;
            QColor focusedBackground;
            QColor text;
            QColor focusedText;
            // int margin;
        } header;

        struct {
            QColor border;
            QColor background;
            QColor selection;
            QColor focusedLine;
            QColor text;
            QString styleSheet;
            // int margin;
        } input;
    } splits;

    struct {
        QPixmap copy;
        QPixmap pin;
    } buttons;

    void normalizeColor(QColor &color);
    void update();
    QColor blendColors(const QColor &color1, const QColor &color2, qreal ratio);

    pajlada::Signals::NoArgSignal updated;

    QStringSetting themeName{"/appearance/theme/name", "Dark"};
    DoubleSetting themeHue{"/appearance/theme/hue", 0.0};

private:
    bool isLight_ = false;
    void actuallyUpdate(double hue, double multiplier);

    pajlada::Signals::NoArgSignal repaintVisibleChatWidgets_;

    friend class WindowManager;
};

Theme *getTheme();
}  // namespace chatterino
