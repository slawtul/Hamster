/*
 * Copyright (c) 2021 Slawek Tuleja
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "MainWindow.h"

MainWindow::MainWindow()
{
    set_border_width(0);
    set_resizable(false);
    set_default_size(360, -1);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);

    header_bar.set_show_close_button(true);
    header_bar.set_title(_("Hamster"));
    header_bar.set_subtitle(_("Clipboard manager"));
    header_bar.pack_end(menu_btn);
    set_titlebar(header_bar);

    add(layout);

    // ABOUT DIALOG
    about_dialog.set_transient_for(*this);
    menu_btn.settings_popover.about_btn
            .signal_clicked()
            .connect(sigc::mem_fun(*this, &MainWindow::show_about_dialog));
    about_dialog
            .signal_response()
            .connect(sigc::mem_fun(*this, &MainWindow::hide_about_dialog));

    // PREFERENCES WINDOW
    preferences_window.set_transient_for(*this);
    menu_btn.settings_popover.pref_btn
            .signal_clicked()
            .connect(sigc::mem_fun(*this, &MainWindow::show_preferences_window));


    // SHORTCUTS WINDOW
    shortcuts_window.set_transient_for(*this);
    menu_btn.settings_popover.shortcuts_btn
            .signal_clicked()
            .connect(sigc::mem_fun(*this, &MainWindow::show_shortcuts_window));

    // QUIT APP
    menu_btn.settings_popover.quit_btn
            .signal_clicked()
            .connect(sigc::mem_fun(*this, &MainWindow::close_app));
}

MainWindow::~MainWindow() = default;

void MainWindow::show_about_dialog()
{
    about_dialog.show();
    about_dialog.present();
}

void MainWindow::hide_about_dialog(int response_id)
{
    if (response_id == Gtk::ResponseType::RESPONSE_DELETE_EVENT)
    {
        about_dialog.hide();
    }
}

void MainWindow::show_shortcuts_window()
{
    shortcuts_window.show();
    shortcuts_window.present();
}

void MainWindow::show_preferences_window()
{
    preferences_window.show();
    preferences_window.present();
}

void MainWindow::close_app()
{
    menu_btn.settings_popover.remove();
    exit(0);
}