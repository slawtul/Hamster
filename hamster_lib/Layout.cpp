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

#include "Layout.h"

Layout::Layout() : listViewText(1, false, Gtk::SELECTION_MULTIPLE), button("OK")
{
    searchEntry.signal_search_changed().connect(sigc::mem_fun(*this, &Layout::on_search_change));
    searchEntry.set_margin_top(6);
    searchEntry.set_margin_right(6);
    searchEntry.set_margin_bottom(6);
    searchEntry.set_margin_left(6);

    pack_start(searchEntry);
    pack_start(separator);
    pack_start(scrolledWindow);
    //pack_start(button);

    button.signal_clicked().connect(sigc::mem_fun(*this, &Layout::on_items_select));

    scrolledWindow.set_size_request(-1, 640);
    scrolledWindow.add(listViewText);

    listViewText.set_column_title(0, "");
    listViewText.set_headers_visible(false);
    listViewText.set_enable_search(false);
    listViewText.prepend("...");
    listViewText.prepend("Hello world of C++!");

    Glib::ustring str = "Gkt3 rules! gtkmm and c++ and clion, and much more...";
    str = str.substr(0, 38).append("...");

    listViewText.prepend(str);
    listViewText.prepend("Welcome to Hamster");
    listViewText.signal_selection_received().connect(sigc::mem_fun(*this, &Layout::on_selection));
    button.signal_focus().connect(sigc::mem_fun(*this, &Layout::on_focus));
}

Layout::~Layout() = default;

void Layout::on_search_change()
{
    g_print("%s", searchEntry.get_text().c_str());
}

void Layout::on_selection(const Gtk::SelectionData &selection_data, guint time)
{
    g_print("on selection");
    g_print("_");
}

bool Layout::on_focus(Gtk::DirectionType direction)
{
    g_print("%d", direction);
    g_print("on focus");
    return false;
}

void Layout::on_items_select()
{
//    for (int item_idx : listViewText.get_selected()) {
//        std::cout << "items selected: " << item_idx << "\n";
//    }
    g_print("%s", searchEntry.get_text().c_str());

    for (int item_idx : listViewText.get_selected())
    {
        g_print("%d", item_idx);
        g_print("\n");
    }

}