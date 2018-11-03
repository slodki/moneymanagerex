/*******************************************************
 Copyright (C) 2018 Tomasz Słodkowicz

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ********************************************************/
#pragma once

#include "Model_Account.h"
#include <wx/wizard.h>
class wxFrame;
class wxDatePickerCtrl;
class mmTextCtrl;

class reconcileWizard : public wxWizard
{
public:
    reconcileWizard(Model_Account::Data* account, wxFrame *frame);
    bool RunIt();

private:
    Model_Account::Data* m_account;
    wxWizardPageSimple *intro, *select_dates, *date_problems;
    wxDatePickerCtrl *fromDateCtrl, *toDateCtrl;
    mmTextCtrl *initialAmount, *finalAmount;
    void OneforePageChanged(wxWizardEvent& event);

    wxDECLARE_EVENT_TABLE();
};
