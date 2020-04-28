// Copyright (c) 2016-2019 The Girauno developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef GIRAUNOADDRESSVALIDATOR_H
#define GIRAUNOADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class GiraunoAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit GiraunoAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Girauno address widget validator, checks for a valid girauno address.
 */
class GiraunoAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit GiraunoAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // GIRAUNOADDRESSVALIDATOR_H
