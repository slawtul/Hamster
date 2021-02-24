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

#include "WindowLayout.h"

WindowLayout::WindowLayout() : item_list(1, false, Gtk::SELECTION_MULTIPLE)
{
    ref_clipboard = Gtk::Clipboard::get();
    ref_clipboard->signal_owner_change().connect(sigc::mem_fun(*this, &WindowLayout::on_clipboard_change));

    search_entry.signal_search_changed().connect(sigc::mem_fun(*this, &WindowLayout::on_search_change));
    search_entry.set_margin_top(4);
    search_entry.set_margin_right(4);
    search_entry.set_margin_bottom(4);
    search_entry.set_margin_left(4);

    pack_start(search_entry);
    pack_start(separator);
    pack_start(scrolled_win);

    scrolled_win.set_size_request(-1, 640);
    scrolled_win.add(item_list);

    ref_item_store = Gtk::ListStore::create(columns);
    item_list.set_model(ref_item_store);
    item_list.set_headers_visible(false);
    item_list.set_enable_search(false);
    item_list.set_search_entry(search_entry);
}

void WindowLayout::on_search_change()
{
    g_print("%s\n", search_entry.get_text().c_str());
}

void WindowLayout::on_clipboard_change(GdkEventOwnerChange *event)
{
    if (event == nullptr) {
        return;
    }
    auto text = ref_clipboard->wait_for_text();
    auto row = *(ref_item_store->prepend());
    row[columns.item_name] = text;
}

