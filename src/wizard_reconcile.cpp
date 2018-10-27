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

#include "wizard_reconcile.h"
#include "mmSimpleDialogs.h"
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/datectrl.h>
#include <wx/msgdlg.h> 

//----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(reconcileWizard, wxWizard)
  EVT_WIZARD_BEFORE_PAGE_CHANGED(wxID_ANY, reconcileWizard::OneforePageChanged)
END_EVENT_TABLE()

reconcileWizard::reconcileWizard(Model_Account::Data* account, wxFrame *frame)
    : wxWizard(frame, wxID_ANY, _("Reconcilation Wizard"))
    , m_account(account)
{
    intro = new wxWizardPageSimple(this);
    wxString introMsg;
    introMsg << _("The next pages will help you create a new database.\n\n"
               "Your database file is stored with an extension of .mmb.\n"
               "As this file contains important financial information,\n"
               "we recommended creating daily backups with the Options\n"
               "setting: 'Backup before opening', and store your backups\n"
               "in a separate location.\n\n"
               "The database can later be encrypted if required, by\n"
               "using the option: 'Save database as' and changing the\n"
               "file type before saving.");
    new wxStaticText(intro, wxID_ANY, introMsg);

    select_dates = new wxWizardPageSimple(this);
    wxBoxSizer *dates_sizer = new wxBoxSizer(wxVERTICAL);
    select_dates->SetSizer(dates_sizer);

    wxStaticText *instruction = new wxStaticText(select_dates, wxID_ANY,
        _("Click on Finish to open our download webpage."));
    m_fromDateCtrl = new wxDatePickerCtrl(select_dates, wxID_FIRST, wxDefaultDateTime
        , wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
    m_toDateCtrl = new wxDatePickerCtrl(select_dates, wxID_LAST, wxDefaultDateTime
        , wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);

    dates_sizer->Add(instruction);
    dates_sizer->Add(m_fromDateCtrl);
    dates_sizer->Add(m_toDateCtrl);

    date_problems = new wxWizardPageSimple(this);
    wxString datesMsg;
    introMsg << _("The next pages will help you create a new database.\n\n"
               "Your database file is stored with an extension of .mmb.\n"
               "As this file contains important financial information,\n"
               "we recommended creating daily backups with the Options\n"
               "setting: 'Backup before opening', and store your backups\n"
               "in a separate location.\n\n"
               "The database can later be encrypted if required, by\n"
               "using the option: 'Save database as' and changing the\n"
               "file type before saving.");
    new wxStaticText(date_problems, wxID_ANY, datesMsg);

    intro->Chain(select_dates)
          .Chain(date_problems);
    GetPageAreaSizer()->Add(intro);
}

bool reconcileWizard::RunIt()
{
  return RunWizard(intro);
}

void reconcileWizard::OneforePageChanged(wxWizardEvent& event)
{
  if (event.GetPage() == select_dates && event.GetDirection() &&
      m_fromDateCtrl->GetValue() >= m_toDateCtrl->GetValue())
    {
      mmErrorDialogs::ToolTip4Object(m_fromDateCtrl, "please select earlier date", "invalid date", wxICON_ERROR);
      event.Veto();
    }
}