/*      _______   __   __   __   ______   __   __   _______   __   __
 *     / _____/\ / /\ / /\ / /\ / ____/\ / /\ / /\ / ___  /\ /  |\/ /\
 *    / /\____\// / // / // / // /\___\// /_// / // /\_/ / // , |/ / /
 *   / / /__   / / // / // / // / /    / ___  / // ___  / // /| ' / /
 *  / /_// /\ / /_// / // / // /_/_   / / // / // /\_/ / // / |  / /
 * /______/ //______/ //_/ //_____/\ /_/ //_/ //_/ //_/ //_/ /|_/ /
 * \______\/ \______\/ \_\/ \_____\/ \_\/ \_\/ \_\/ \_\/ \_\/ \_\/
 *
 * Copyright (c) 2004 - 2008 Olof Naess�n and Per Larsson
 *
 *
 * Per Larsson a.k.a finalman
 * Olof Naess�n a.k.a jansem/yakslem
 *
 * Visit: http://guichan.sourceforge.net
 *
 * License: (BSD)
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Guichan nor the names of its contributors may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FCN_WIDGET_HPP
#define FCN_WIDGET_HPP

#include <list>
#include <string>

#include "fifechan/color.hpp"
#include "fifechan/rectangle.hpp"
#include "fifechan/widgetlistener.hpp"

namespace fcn
{
    class ActionListener;
    class DeathListener;
    class DefaultFont;
    class FocusHandler;
    class FocusListener;
    class Font;
    class Graphics;
    class KeyInput;
    class KeyListener;
    class MouseInput;
    class MouseListener;
    class VisibilityEventHandler;
    class WidgetListener;

    /**
     * Abstract class for widgets of Guichan. It contains basic functions 
     * every widget should have.
     *
     * NOTE: Functions begining with underscore "_" should not
     *       be overloaded unless you know what you are doing.
     *
     * @author Olof Naess�n
     * @author Per Larsson
     * @since 0.1.0
     */
    class FCN_CORE_DECLSPEC Widget
    {
    public:
        /**
         * Constructor. Resets member variables. Noteable, a widget is not
         * focusable as default, therefore, widgets that are supposed to be
         * focusable should overide this default in their own constructor.
         */
        Widget();

        /**
         * Default destructor.
         */
        virtual ~Widget();

        /**
         * Draws the widget. The call to draw is initiated by the widget's
         * parent. The graphics object is set up so that all drawing is relative 
         * to the widget, i.e coordinate (0,0) is the top left corner of the widget. 
         * It is not possible to draw outside of a widget's dimension. If a widget
         * has children, the parent's draw function will always be called before
         * the children's draw functions are called.
         *
         * NOTE: A widget with children won't draw its children unless the
         *       children area given by Widget::getChildrenArea returns a
         *       none empty rectangle inside the widgets dimension. The children
         *       area is considered relative to the widget's position.
         *
         * @param graphics A graphics object to draw with.
         * @see getChildrenArea
         * @since 0.1.0
         */
        virtual void draw(Graphics* graphics) = 0;

        /**
         * Called when a widget is given a chance to draw a frame around itself.
         * The frame is not considered a part of the widget, it only allows a frame
         * to be drawn around the widget, thus a frame will never be included when
         * calculating if a widget should receive events from user input. Also
         * a widget's frame will never be included when calculating a widget's 
         * position.
         * 
         * The size of the frame is calculated using the widget's frame size. 
         * If a widget has a frame size of 10 pixels than the area the drawFrame 
         * function can draw to will be the size of the widget with an additional 
         * extension of 10 pixels in each direction.
         *
         * An example when drawFrame is a useful function is if a widget needs
         * a glow around itself.
         *
         * @param graphics A graphics object to draw with.
         * @see setFrameSize, getFrameSize
         * @since 0.8.0
         */
        virtual void drawFrame(Graphics* graphics);

        /**
         * Sets the size of the widget's frame. The frame is not considered a part of 
         * the widget, it only allows a frame to be drawn around the widget, thus a frame 
         * will never be included when calculating if a widget should receive events 
         * from user input. Also a widget's frame will never be included when calculating
         * a widget's position.
         *
         * A frame size of 0 means that the widget has no frame. The default frame size
         * is 0.
         *
         * @param frameSize The size of the widget's frame.
         * @see getFrameSize, drawFrame
         * @since 0.8.0
         */
        void setFrameSize(unsigned int frameSize);

        /**
         * Gets the size of the widget's frame. The frame is not considered a part of 
         * the widget, it only allows a frame to be drawn around the widget, thus a frame 
         * will never be included when calculating if a widget should receive events 
         * from user input. Also a widget's frame will never be included when calculating
         * a widget's position.
         *
         * A frame size of 0 means that the widget has no frame. The default frame size
         * is 0.
         *
         * @return The size of the widget's frame.
         * @see setFrameSize, drawFrame
         * @since 0.8.0
         */
        unsigned int getFrameSize() const;

        /**
         * Called for all widgets in the gui each time Gui::logic is called.
         * You can do logic stuff here like playing an animation.
         *
         * @see Gui::logic
         * @since 0.1.0
         */
        virtual void logic() { }

        /**
         * Gets the widget's parent container.
         *
         * @return The widget's parent container. NULL if the widget
         *         has no parent.
         * @since 0.1.0
         */
        virtual Widget* getParent() const;

        /**
         * Gets the top widget, or top parent, of this widget.
         *
         * @return The top widget, or top parent, for this widget. NULL if no top widget
         *         exists (that is this widget doesn't have a parent).
         * @since 0.9.0
         */
        virtual Widget* getTop() const;

        /**
         * Sets the width of the widget.
         *
         * @param width The width of the widget.
         * @see getWidth, setHeight, getHeight, setSize,
         *      setDimension, getDimensi
         * @since 0.1.0
         */
        void setWidth(int width);

        /**
         * Gets the width of the widget.
         *
         * @return The width of the widget.
         * @see setWidth, setHeight, getHeight, setSize,
         *      setDimension, getDimension
         * @since 0.1.0
         */
        int getWidth() const;

        /**
         * Sets the height of the widget.
         *
         * @param height The height of the widget.
         * @see getHeight, setWidth, getWidth, setSize,
         *      setDimension, getDimension
         * @since 0.1.0
         */
        void setHeight(int height);

        /**
         * Gets the height of the widget.
         *
         * @return The height of the widget.
         * @see setHeight, setWidth, getWidth, setSize,
         *      setDimension, getDimension
         * @since 0.1.0
         */
        int getHeight() const;

        /**
         * Sets the size of the widget.
         *
         * @param width The width of the widget.
         * @param height The height of the widget.
         * @see setWidth, setHeight, getWidth, getHeight,
         *      setDimension, getDimension
         * @since 0.1.0
         */
        void setSize(int width, int height);

        /**
         * Sets the x coordinate of the widget. The coordinate is
         * relateive to the widget's parent.
         *
         * @param x The x coordinate of the widget.
         * @see getX, setY, getY, setPosition, setDimension, getDimension
         * @since 0.1.0
         */
        void setX(int x);

        /**
         * Gets the x coordinate of the widget. The coordinate is
         * relative to the widget's parent.
         *
         * @return The x coordinate of the widget.
         * @see setX, setY, getY, setPosition, setDimension, getDimension
         * @since 0.1.0
         */
        int getX() const;

        /**
         * Sets the y coordinate of the widget. The coordinate is
         * relative to the widget's parent.
         *
         * @param y The y coordinate of the widget.
         * @see setY, setX, getX, setPosition, setDimension, getDimension
         * @since 0.1.0
         */
        void setY(int y);

        /**
         * Gets the y coordinate of the widget. The coordinate is
         * relative to the widget's parent.
         *
         * @return The y coordinate of the widget.
         * @see setY, setX, getX, setPosition, setDimension, getDimension
         * @since 0.1.0
         */
        int getY() const;

        /**
         * Sets position of the widget. The position is relative
         * to the widget's parent.
         *
         * @param x The x coordinate of the widget.
         * @param y The y coordinate of the widget.
         * @see setX, getX, setY, getY, setDimension, getDimension
         * @since 0.1.0
         */
        void setPosition(int x, int y);

        /**
         * Sets the dimension of the widget. The dimension is
         * relative to the widget's parent.
         *
         * @param dimension The dimension of the widget.
         * @see getDimension, setX, getX, setY, getY, setPosition
         * @since 0.1.0
         */
        void setDimension(const Rectangle& dimension);

        /**
         * Gets the dimension of the widget. The dimension is
         * relative to the widget's parent.
         *
         * @return The dimension of the widget.
         * @see getDimension, setX, getX, setY, getY, setPosition
         * @since 0.1.0
         */
        const Rectangle& getDimension() const;

        /**
         * Sets the widget to be fosusable, or not.
         *
         * @param focusable True if the widget should be focusable,
         *                  false otherwise.
         * @see isFocusable
         * @since 0.1.0
         */
        void setFocusable(bool focusable);

         /**
         * Checks if a widget is focsable.
         *
         * @return True if the widget should be focusable, false otherwise.
         * @see setFocusable
         * @since 0.1.0
         */
        bool isFocusable() const;

        /**
         * Checks if the widget is focused.
         *
         * @return True if the widget is focused, false otherwise.
         * @since 0.1.0
         */
        virtual bool isFocused() const;

        /**
         * Sets the widget to enabled, or not. A disabled
         * widget will never recieve mouse or key events.
         *
         * @param enabled True if widget should be enabled,
         *                false otherwise.
         * @see isEnabled
         * @since 0.1.0
         */
        void setEnabled(bool enabled);

        /**
         * Checks if the widget is enabled. A disabled
         * widget will never recieve mouse or key events.
         *
         * @return True if widget is enabled, false otherwise.
         * @see setEnabled
         * @since 0.1.0
         */
        bool isEnabled() const;

        /**
         * Sets the widget to be visible, or not.
         *
         * @param visible True if widget should be visible, false otherwise.
         * @see isVisible
         * @since 0.1.0
         */
        void setVisible(bool visible);

        /**
         * Checks if the widget is visible.
         *
         * @return True if widget is be visible, false otherwise.
         * @see setVisible
         * @since 0.1.0
         */
        bool isVisible() const;

        /**
         * Sets the base color of the widget.
         *
         * @param color The baseground color.
         * @see getBaseColor
         * @since 0.1.0
         */
        void setBaseColor(const Color& color);

        /**
         * Gets the base color.
         *
         * @return The base color.
         * @see setBaseColor
         * @since 0.1.0
         */
        const Color& getBaseColor() const;

        /**
         * Sets the foreground color.
         *
         * @param color The foreground color.
         * @see getForegroundColor
         * @since 0.1.0
         */
        void setForegroundColor(const Color& color);

        /**
         * Gets the foreground color.
         *
         * @see setForegroundColor
         * @since 0.1.0
         */
        const Color& getForegroundColor() const;

        /**
         * Sets the background color.
         *
         * @param color The background Color.
         * @see setBackgroundColor
         * @since 0.1.0
         */
        void setBackgroundColor(const Color& color);

        /**
         * Gets the background color.
         *
         * @see setBackgroundColor
         * @since 0.1.0
         */
        const Color& getBackgroundColor() const;

        /**
         * Sets the selection color.
         *
         * @param color The selection color.
         * @see getSelectionColor
         * @since 0.6.0
         */
        void setSelectionColor(const Color& color);

        /**
         * Gets the selection color.
         *
         * @return The selection color.
         * @see setSelectionColor
         * @since 0.6.0
         */
        const Color& getSelectionColor() const;
        
        /**
         * Requests focus for the widget. A widget will only recieve focus
         * if it is focusable.
         *
         * @since 0.1.0
         */
        virtual void requestFocus();

        /**
         * Requests a move to the top in the parent widget.
         *
         * @since 0.1.0
         */
        virtual void requestMoveToTop();

        /**
         * Requests a move to the bottom in the parent widget.
         *
         * @since 0.1.0
         */
        virtual void requestMoveToBottom();

        /**
         * Called whenever a widget should draw itself. The function will
         * set up clip areas and call the draw function for this widget
         * and for all its children.
         *
         * WARNING: This function is used internally and should not
         *          be called or overloaded unless you know what you
         *          are doing.
         * @since 0.9.0
         */
        virtual void _draw(Graphics* graphics);

         /**
         * Called whenever a widget should perform logic. The function will
         * call the logic function for this widget and for all its children.
         *
         * WARNING: This function is used internally and should not
         *          be called or overloaded unless you know what you
         *          are doing.
         * @since 0.9.0
         */
        virtual void _logic();

        /**
         * Sets the focus handler to be used.
         *
         * WARNING: This function is used internally and should not
         *          be called or overloaded unless you know what you
         *          are doing.
         *
         * @param focusHandler The focus handler to use.
         * @see _getFocusHandler
         * @since 0.1.0
         */
        virtual void _setFocusHandler(FocusHandler* focusHandler);
        
        /**
         * Gets the focus handler used.
         *
         * WARNING: This function is used internally and should not
         *          be called or overloaded unless you know what you
         *          are doing.
         *
         * @return The focus handler used.
         * @see _setFocusHandler
         * @since 0.1.0
         */
        virtual FocusHandler* _getFocusHandler();
        
        /**
         * Adds an action listener to the widget. When an action event 
         * is fired by the widget the action listeners of the widget 
         * will get notified.
         *
         * @param actionListener The action listener to add.
         * @see removeActionListener
         * @since 0.1.0
         */
        void addActionListener(ActionListener* actionListener);

        /**
         * Removes an added action listener from the widget.
         *
         * @param actionListener The action listener to remove.
         * @see addActionListener
         * @since 0.1.0
         */
        void removeActionListener(ActionListener* actionListener);

        /**
         * Adds a death listener to the widget. When a death event is 
         * fired by the widget the death listeners of the widget will 
         * get notified.
         *
         * @param deathListener The death listener to add.
         * @see removeDeathListener
         * @since 0.1.0
         */
        void addDeathListener(DeathListener* deathListener);

        /**
         * Removes an added death listener from the widget.
         *
         * @param deathListener The death listener to remove.
         * @see addDeathListener
         * @since 0.1.0
         */
        void removeDeathListener(DeathListener* deathListener);

        /**
         * Adds a mouse listener to the widget. When a mouse event is 
         * fired by the widget the mouse listeners of the widget will 
         * get notified.
         *
         * @param mouseListener The mouse listener to add.
         * @see removeMouseListener
         * @since 0.1.0
         */
        void addMouseListener(MouseListener* mouseListener);

        /**
         * Removes an added mouse listener from the widget.
         *
         * @param mouseListener The mouse listener to remove.
         * @see addMouseListener
         * @since 0.1.0
         */
        void removeMouseListener(MouseListener* mouseListener);

        /**
         * Adds a key listener to the widget. When a key event is 
         * fired by the widget the key listeners of the widget will 
         * get notified.
         *
         * @param keyListener The key listener to add.
         * @see removeKeyListener
         * @since 0.1.0
         */
        void addKeyListener(KeyListener* keyListener);

        /**
         * Removes an added key listener from the widget.
         *
         * @param keyListener The key listener to remove.
         * @see addKeyListener
         * @since 0.1.0
         */
        void removeKeyListener(KeyListener* keyListener);

        /**
         * Adds a focus listener to the widget. When a focus event is 
         * fired by the widget the key listeners of the widget will 
         * get notified.
         *
         * @param focusListener The focus listener to add.
         * @see removeFocusListener
         * @since 0.7.0
         */
        void addFocusListener(FocusListener* focusListener);

        /**
         * Removes an added focus listener from the widget.
         *
         * @param focusListener The focus listener to remove.
         * @see addFocusListener
         * @since 0.7.0
         */
        void removeFocusListener(FocusListener* focusListener);

        /**
         * Adds a widget listener to the widget. When a widget event is 
         * fired by the widget the key listeners of the widget will 
         * get notified.
         *
         * @param widgetListener The widget listener to add.
         * @see removeWidgetListener
         * @since 0.8.0
         */
        void addWidgetListener(WidgetListener* widgetListener);

        /**
         * Removes an added widget listener from the widget.
         *
         * @param widgetListener The widget listener to remove.
         * @see addWidgetListener
         * @since 0.8.0
         */
        void removeWidgetListener(WidgetListener* widgetListener);

        /**
         * Sets the action event identifier of the widget. The identifier is
         * used to be able to identify which action has occured.
         *
         * NOTE: An action event identifier should not be used to identify a
         *       certain widget but rather a certain event in your application.
         *       Several widgets can have the same action event identifer.
         *
         * @param actionEventId The action event identifier.
         * @see getActionEventId
         * @since 0.6.0
         */
        void setActionEventId(const std::string& actionEventId);

        /**
         * Gets the action event identifier of the widget.
         *
         * @return The action event identifier of the widget.
         * @see setActionEventId
         * @since 0.6.0
         */
        const std::string& getActionEventId() const;

        /**
         * Gets the absolute position on the screen for the widget.
         *
         * @param x The absolute x coordinate will be stored in this parameter.
         * @param y The absolute y coordinate will be stored in this parameter.
         * @since 0.1.0
         */
        virtual void getAbsolutePosition(int& x, int& y) const;

        /**
         * Sets the parent of the widget. A parent must be a BasicContainer.
         *
         * WARNING: This function is used internally and should not
         *          be called or overloaded unless you know what you
         *          are doing.
         *
         * @param parent The parent of the widget.
         * @see getParent
         * @since 0.1.0
         */
        virtual void _setParent(Widget* parent);

        /**
         * Gets the font set for the widget. If no font has been set, 
         * the global font will be returned. If no global font has been set, 
         * the default font will be returend.
         *
         * @return The font set for the widget.
         * @see setFont, setGlobalFont
         * @since 0.1.0
         */
        Font *getFont() const;

        /**
         * Sets the global font to be used by default for all widgets.
         *
         * @param font The global font.
         * @see getGlobalFont
         * @since 0.1.0
         */
        static void setGlobalFont(Font* font);

        /**
         * Sets the font for the widget. If NULL is passed, the global font 
         * will be used.
         *
         * @param font The font to set for the widget.
         * @see getFont
         * @since 0.1.0
         */
        void setFont(Font* font);

        /**
         * Called when the font has changed. If the change is global,
         * this function will only be called if the widget doesn't have a
         * font already set.
         *
         * @since 0.1.0
         */
        virtual void fontChanged() { }

        /**
         * Checks if a widget exists or not, that is if it still exists
         * an instance of the object.
         *
         * @param widget The widget to check.
         * @return True if an instance of the widget exists, false otherwise.
         * @since 0.1.0
         */
        static bool widgetExists(const Widget* widget);

        /**
         * Checks if tab in is enabled. Tab in means that you can set focus
         * to this widget by pressing the tab button. If tab in is disabled
         * then the focus handler will skip this widget and focus the next
         * in its focus order.
         *
         * @return True if tab in is enabled, false otherwise.
         * @see setTabInEnabled
         * @since 0.1.0
         */
        bool isTabInEnabled() const;

        /**
         * Sets tab in enabled, or not. Tab in means that you can set focus
         * to this widget by pressing the tab button. If tab in is disabled
         * then the FocusHandler will skip this widget and focus the next
         * in its focus order.
         *
         * @param enabled True if tab in should be enabled, false otherwise.
         * @see isTabInEnabled
         * @since 0.1.0
         */
        void setTabInEnabled(bool enabled);

        /**
         * Checks if tab out is enabled. Tab out means that you can lose
         * focus to this widget by pressing the tab button. If tab out is
         * disabled then the FocusHandler ignores tabbing and focus will
         * stay with this widget.
         *
         * @return True if tab out is enabled, false otherwise.
         * @see setTabOutEnabled
         * @since 0.1.0
         */
        bool isTabOutEnabled() const;

        /**
         * Sets tab out enabled. Tab out means that you can lose
         * focus to this widget by pressing the tab button. If tab out is
         * disabled then the FocusHandler ignores tabbing and focus will
         * stay with this widget.
         *
         * @param enabled True if tab out should be enabled, false otherwise.
         * @see isTabOutEnabled
         * @since 0.1.0
         */
        void setTabOutEnabled(bool enabled);

        /**
         * Requests modal focus. When a widget has modal focus, only that
         * widget and it's children may recieve input.
         *
         * @throws Exception if another widget already has modal focus.
         * @see releaseModalFocus, isModalFocused
         * @since 0.4.0
         */
        virtual void requestModalFocus();

        /**
         * Requests modal mouse input focus. When a widget has modal input focus
         * that widget will be the only widget receiving input even if the input
         * occurs outside of the widget and no matter what the input is.
         *
         * @throws Exception if another widget already has modal focus.
         * @see releaseModalMouseInputFocus, isModalMouseInputFocused
         * @since 0.6.0
         */
        virtual void requestModalMouseInputFocus();

        /**
         * Releases modal focus. Modal focus will only be released if the
         * widget has modal focus.
         *
         * @see requestModalFocus, isModalFocused
         * @since 0.4.0
         */
        virtual void releaseModalFocus();

        /**
         * Releases modal mouse input focus. Modal mouse input focus will only
         * be released if the widget has modal mouse input focus.
         *
         * @see requestModalMouseInputFocus, isModalMouseInputFocused
         * @since 0.6.0
         */
        virtual void releaseModalMouseInputFocus();

        /**
         * Checks if the widget or it's parent has modal focus.
         *
         * @return True if the widget has modal focus, false otherwise.
         * @see requestModalFocus, releaseModalFocus
         * @since 0.8.0
         */
        virtual bool isModalFocused() const;

        /**
         * Checks if the widget or it's parent has modal mouse input focus.
         *
         * @return True if the widget has modal mouse input focus, false
         *         otherwise.
         * @see requestModalMouseInputFocus, releaseModalMouseInputFocus
         * @since 0.8.0
         */
        virtual bool isModalMouseInputFocused() const;

        /**
         * Gets a widget at a certain position in the widget.
         * This function is used to decide which gets mouse input,
         * thus it can be overloaded to change that behaviour.
         *
         * NOTE: This always returns NULL if the widget is not
         *       a container.
         *
         * @param x The x coordinate of the widget to get.
         * @param y The y coordinate of the widget to get.
         * @param exclude Widget to exclude from search, if NULL
         *            no widgets get excluded.
         * @return The widget at the specified coodinate, NULL
         *         if no widget is found.
         * @since 0.6.0
         */
        virtual Widget *getWidgetAt(int x, int y, Widget* exclude = NULL);

        /**
         * Gets all widgets inside a certain area of the widget.
         *
         * NOTE: This always returns an emtpy list if the widget is not
         *       a container.
         *
         * @param area The area to check.
         * @param ignore If supplied, this widget will be ignored.
         * @return A list of widgets. An empty list if no widgets was found.
         * @since 0.9.0
         */
        virtual std::list<Widget*> getWidgetsIn(const Rectangle& area, 
                                                Widget* ignore = NULL);

        /**
         * Gets the mouse listeners of the widget.
         *
         * @return The mouse listeners of the widget.
         * @since 0.6.0
         */
        virtual const std::list<MouseListener*>& _getMouseListeners();

        /**
         * Gets the key listeners of the widget.
         *
         * @return The key listeners of the widget.
         * @since 0.6.0
         */
        virtual const std::list<KeyListener*>& _getKeyListeners();

        /**
         * Gets the focus listeners of the widget.
         *
         * @return The focus listeners of the widget.
         * @since 0.7.0
         */
        virtual const std::list<FocusListener*>& _getFocusListeners();

        /**
         * Gets the area of the widget occupied by the widget's children.
         * By default this method returns an empty rectangle as not all
         * widgets are containers. If you want to make a container this
         * method should return the area where the children resides. This
         * method is used when drawing children of a widget when computing
         * clip rectangles for the children.
         *
         * NOTE: The returned rectangle should be relative to the widget,
         *       i.e a rectangle with x and y coordinate (0,0) and with
         *       width and height the same as the widget will let the 
         *       children draw themselves in the whole widget.
         *
         * An example of a widget that overloads this method is ScrollArea.
         * A ScrollArea has a view of its contant and that view is the
         * children area. The size of a ScrollArea's children area might
         * vary depending on if the scroll bars of the ScrollArea is shown
         * or not.
         *
         * @return The area of the widget occupied by the widget's children.
         * @since 0.5.0
         */
        virtual Rectangle getChildrenArea();

        /**
         * Gets the internal focus handler used.
         *
         * @return the internalFocusHandler used. If no internal focus handler
         *         is used, NULL will be returned.
         * @see setInternalFocusHandler
         * @since 0.1.0
         */
        virtual FocusHandler* _getInternalFocusHandler();

        /**
         * Sets the internal focus handler. An internal focus handler is
         * needed if both a widget in the widget and the widget itself
         * should be foucsed at the same time.
         *
         * @param focusHandler The internal focus handler to be used.
         * @see getInternalFocusHandler
         * @since 0.1.0
         */
        void setInternalFocusHandler(FocusHandler* internalFocusHandler);

        /**
         * Moves a widget to the top of this widget. The moved widget will be
         * drawn above all other widgets in this widget.
         *
         * This method is safe to call at any time.
         *
         * @param widget The widget to move to the top.
         * @see moveToBottom
         * @since 0.1.0
         */
        virtual void moveToTop(Widget* widget);

        /**
         * Moves a widget in this widget to the bottom of this widget.
         * The moved widget will be drawn below all other widgets in this widget.
         *
         * This method is safe to call at any time.
         *
         * @param widget The widget to move to the bottom.
         * @see moveToTop
         * @since 0.1.0
         */
        virtual void moveToBottom(Widget* widget);

        /**
         * Focuses the next widget in the widget.
         * 
         * @see moveToBottom
         * @since 0.1.0
         */
        virtual void focusNext();

        /**
         * Focuses the previous widget in the widget.
         *
         * @see moveToBottom
         * @since 0.1.0
         */
        virtual void focusPrevious();

        /**
         * Tries to show a specific part of a widget by moving it. Used if the
         * widget should act as a container.
         *
         * @param widget The target widget.
         * @param area The area to show.
         * @since 0.1.0
         */
        virtual void showWidgetPart(Widget* widget, Rectangle area);

        /**
         * Sets an id of a widget. An id can be useful if a widget needs to be
         * identified in a container. For example, if widgets are created by an
         * XML document, a certain widget can be retrieved given that the widget
         * has an id.
         *
         * @param id The id to set to the widget.
         * @see getId, BasicContainer::findWidgetById
         * @since 0.8.0
         */
        void setId(const std::string& id);

        /**
         * Gets the id of a widget. An id can be useful if a widget needs to be
         * identified in a container. For example, if widgets are created by an
         * XML document, a certain widget can be retrieved given that the widget
         * has an id.
         *
         * @param id The id to set to the widget.
         * @see setId, BasicContainer::findWidgetById
         * @since 0.8.0
         */
        const std::string& getId() const;

        /**
         * Shows a certain part of a widget in the widget's parent.
         * Used when widgets want a specific part to be visible in
         * its parent. An example is a TextArea that wants a specific
         * part of its text to be visible when a TextArea is a child
         * of a ScrollArea.
         *
         * @param rectangle The rectangle to be shown.
         * @since 0.8.0
         */
        virtual void showPart(Rectangle rectangle);
    
        /**
         * Sets the visibility event handler to be used.
         * 
         * WARNING: This function is used internally and should not
         *          be called unless you know what you
         *          are doing.
         * 
         * FIXME We don't like the visibility handler being static
         *        but we leave it as is for the moment, until we
         *        come up a better solution.
         * 
         * @param visibilityEventHandler The visibility event handler to be used.
         */
        static void _setVisibilityEventHandler(VisibilityEventHandler* visibilityEventHandler);
        
        /**
         * Gets the visibility event handler of this widget.
         * 
         * WARNING: This function is used internally and should not
         *          be called unless you know what you
         *          are doing.
         * 
         * FIXME We don't like the visibility handler being static
         *        but we leave it as is for the moment, until we
         *        come up a better solution.
         */
        static VisibilityEventHandler* _getVisibilityEventHandler();
        
    protected:
        /**
         * Distributes an action event to all action listeners
         * of the widget.
         *
         * @since 0.8.0
         */
        void distributeActionEvent();

        /**
         * Distributes resized events to all of the widget's listeners.
         *
         * @since 0.8.0
         */
        void distributeResizedEvent();

        /**
         * Distributes moved events to all of the widget's listeners.
         *
         * @since 0.8.0
         */
        void distributeMovedEvent();

        /**
         * Distributes hidden events to all of the widget's listeners.
         *
         * @since 0.8.0
         */
        void distributeHiddenEvent();

        /**
         * Distributes shown events to all of the widget's listeners.
         *
         * @since 0.8.0
         */
        void distributeShownEvent();
        
        /**
         * Distributes ancestor moved events to all of the widget's listeners.
         * All children will also distribute the same event.
         * 
         * @param ancestor Ancestor widget that was moved.
         */
        void distributeAncestorMovedEvent(Widget* ancestor);
        
        /**
         * Distributes ancestor hidden events to all of the widget's listeners.
         * All children will also distribute the same event.
         * 
         * @param ancestor Ancestor widget that was hidden.
         */
        void distributeAncestorHiddenEvent(Widget* ancestor);
        
        /**
         * Distributes ancestor shown events to all of the widget's listeners.
         * All children will also distribute the same event.
         * 
         * @param ancestor Ancestor widget that was shown.
         */
        void distributeAncestorShownEvent(Widget* ancestor);
        
        /**
         * Adds a child to the widget.
         *
         * THIS METHOD IS NOT SAFE TO CALL INSIDE A WIDGETS LOGIC FUNCTION
         * INSIDE ANY LISTER FUNCTIONS!
         *
         * @param widget The widget to add.
         * @see remove, clear
         * @since 0.9.0
         */
        void add(Widget* widget);

        /**
         * Removes a child from the widget.
         *
         * THIS METHOD IS NOT SAFE TO CALL INSIDE A WIDGETS LOGIC FUNCTION
         * INSIDE ANY LISTER FUNCTIONS!
         *
         * @param widget The widget to remove.
         * @see add, clear
         * @since 0.9.0
         */
        virtual void remove(Widget* widget);

        /**
         * Clears the widget from all its children.
         *
         * THIS METHOD IS NOT SAFE TO CALL INSIDE A WIDGETS LOGIC FUNCTION
         * INSIDE ANY LISTER FUNCTIONS!
         *
         * @see remove, clear
         * @since 0.9.0
         */
        virtual void clear();

        /**
         * Finds a widget given an id. This function can be useful
         * when implementing a GUI generator for Guichan, such as
         * the ability to create a Guichan GUI from an XML file.
         *
         * @param id The id to find a widget by.
         * @return The widget with the corrosponding id, 
         *         NULL of no widget is found.
         *
         * @since 0.8.0
         */
        virtual Widget* findWidgetById(const std::string& id);

        /**
         * Resizes the widget to fit it's children exactly.
         *
         * @since 0.9.0
         */
        void resizeToChildren();

        /**
         * Gets the children of the widget.
         *
         * @return A list of the widgets children.
         * @since 0.9.0
         */
        const std::list<Widget*>& getChildren() const;

        /**
         * Holds the mouse listeners of the widget.
         */
        std::list<MouseListener*> mMouseListeners;

        /**
         * Holds the key listeners of the widget.
         */
        std::list<KeyListener*> mKeyListeners;

        /** 
         * Holds the action listeners of the widget.
         */
        std::list<ActionListener*> mActionListeners;

        /**
         * Holds the death listeners of the widget.
         */ 
        std::list<DeathListener*> mDeathListeners;

        /**
         * Holds the focus listeners of the widget.
         */
        std::list<FocusListener*> mFocusListeners;

        /**
         * Holds the widget listeners of the widget.
         */
        std::list<WidgetListener*> mWidgetListeners;

        /**
         * Holds the foreground color of the widget.
         */
        Color mForegroundColor;

        /**
         * Holds the background color of the widget.
         */
        Color mBackgroundColor;

        /**
         * Holds the base color of the widget.
         */
        Color mBaseColor;

        /**
         * Holds the selection color of the widget.
         */
        Color mSelectionColor;

        /**
         * Holds the focus handler used by the widget.
         */
        FocusHandler* mFocusHandler;

        /**
         * Holds the focus handler used by the widget. NULL
         * if no internal focus handler is used.
         */
        FocusHandler* mInternalFocusHandler;
        
        /**
         * Holds the parent of the widget. NULL if the widget
         * has no parent.
         */
        Widget* mParent;

        /**
         * Holds the dimension of the widget.
         */
        Rectangle mDimension;

        /** 
         * Holds the frame size of the widget.
         */
        unsigned int mFrameSize;

        /**
         * Holds the action event of the widget.
         */
        std::string mActionEventId;

        /**
         * True if the widget focusable, false otherwise.
         */
        bool mFocusable;

        /**
         * True if the widget visible, false otherwise.
         */
        bool mVisible;

        /**
         * True if the widget has tab in enabled, false otherwise.
         */
        bool mTabIn;

        /**
         * True if the widget has tab in enabled, false otherwise.
         */
        bool mTabOut;

        /**
         * True if the widget is enabled, false otherwise.
         */
        bool mEnabled;

        /**
         * Holds the id of the widget.
         */
        std::string mId;

        /**
         * Holds the font used by the widget.
         */
        Font* mCurrentFont;

        /**
         * Holds the default font used by the widget.
         */
        static DefaultFont mDefaultFont;

        /**
         * Holds the global font used by the widget.
         */
        static Font* mGlobalFont;

        /**
         * Holds a list of all instances of widgets.
         */
        static std::list<Widget*> mWidgetInstances;
        
        /**
         * Holds the visibility event handler used by the widgets.
         * 
         * FIXME We don't like the visibility handler being static
         *        but we leave it as is for the moment, until we
         *        come up a better solution.
         */
        static VisibilityEventHandler* mVisibilityEventHandler;

        /**
         * Holds all children of the widget.
         */
        std::list<Widget*> mChildren;
    };
}

#endif // end FCN_WIDGET_HPP
