/*
 * Copyright (C) EdgeTX
 *
 * Based on code named
 *   libopenui - https://github.com/opentx/libopenui
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#pragma once

#include <utility>
#include "layer.h"
#include "bitmapbuffer.h"

class MainWindow: public Window
{
  protected:
    // singleton
    MainWindow();

  public:
    ~MainWindow() override
    {
      children.clear();
    }

    static bool isMainWindowCreated()
    {
      return _instance != nullptr;
    }

    static MainWindow * instance()
    {
      if (!_instance)
        _instance = new MainWindow();

      return _instance;
    }

#if defined(TESTS)
    static void create()
    {
      _instance = new MainWindow();
    }
#endif

#if defined(DEBUG_WINDOWS)
    std::string getName() const override
    {
      return "MainWindow";
    }
#endif


    void setActiveScreen() {
      lv_scr_load(lvobj);
    }
  
    void invalidate()
    {
      invalidate({0, 0, rect.w, rect.h});
    }

    void invalidate(const rect_t & rect) override;

    bool needsRefresh() const
    {
      return invalidatedRect.w > 0;
    }

    bool refresh();

    void run(bool trash=true);

  protected:
    static MainWindow * _instance;
    static void emptyTrash();
    rect_t invalidatedRect;
    const char * shutdown = nullptr;
};
