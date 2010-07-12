/* Torsion - http://github.com/special/torsion
 * Copyright (C) 2010, John Brooks <special@dereferenced.net>
 *
 * Torsion is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Torsion. If not, see http://www.gnu.org/licenses/
 */

#ifndef CONTACTSVIEWDELEGATE_H
#define CONTACTSVIEWDELEGATE_H

#include <QAbstractItemDelegate>
#include "ContactItemDelegate.h"
#include "IdentityItemDelegate.h"
#include "ContactsView.h"

class ContactsViewDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
    Q_DISABLE_COPY(ContactsViewDelegate)

public:
    explicit ContactsViewDelegate(ContactsView *view);

    bool indexIsContact(const QModelIndex &index) const;

    bool pageHitTest(const QModelIndex &index, const QSize &size, const QPoint &point, ContactsView::Page &hitPage) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    ContactItemDelegate contactDelegate;
    IdentityItemDelegate identityDelegate;
};

#endif // CONTACTSVIEWDELEGATE_H