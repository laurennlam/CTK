/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkDICOMBrowser_h
#define __ctkDICOMBrowser_h

// Qt includes 
#include <QWidget>

#include "ctkDICOMWidgetsExport.h"

class ctkDICOMBrowserPrivate;
class ctkThumbnailLabel;
class QModelIndex;
class ctkDICOMDatabase;

/// \ingroup DICOM_Widgets
class CTK_DICOM_WIDGETS_EXPORT ctkDICOMBrowser : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(ctkDICOMDatabase* database READ database)
  Q_PROPERTY(QString databaseDirectory READ databaseDirectory WRITE setDatabaseDirectory)
  Q_PROPERTY(bool searchWidgetPopUpMode READ searchWidgetPopUpMode WRITE setSearchWidgetPopUpMode)
  Q_PROPERTY(QStringList tagsToPrecache READ tagsToPrecache WRITE setTagsToPrecache)
  Q_PROPERTY(bool displayImportSummary READ displayImportSummary WRITE setDisplayImportSummary)

public:
  typedef QWidget Superclass;
  explicit ctkDICOMBrowser(QWidget* parent=0);
  virtual ~ctkDICOMBrowser();

  /// Directory being used to store the dicom database
  QString databaseDirectory() const;

  /// See ctkDICOMDatabase for description - these accessors
  /// delegate to the corresponding routines of the internal
  /// instance of the database.
  /// @see ctkDICOMDatabase
  void setTagsToPrecache(const QStringList tags);
  const QStringList tagsToPrecache();

  /// Updates schema of loaded database to match the one
  /// coded by the current version of ctkDICOMDatabase.
  /// Also provides a dialog box for progress
  void updateDatabaseSchemaIfNeeded();

  /// Setting search widget pop-up mode
  /// Default value is false. Setting it to true will make
  /// search widget to be displayed as pop-up widget
  void setSearchWidgetPopUpMode(bool flag);
  bool searchWidgetPopUpMode();
  ctkDICOMDatabase* database();

  /// Option to show or not import summary dialog.
  /// Since the summary dialog is modal, we give the option
  /// of disabling it for batch modes or testing.
  void setDisplayImportSummary(bool);
  bool displayImportSummary();
  /// Accessors to status of last directory import operation
  int patientsAddedDuringImport();
  int studiesAddedDuringImport();
  int seriesAddedDuringImport();
  int instancesAddedDuringImport();

public Q_SLOTS:
  void setDatabaseDirectory(const QString& directory);
  void onFileIndexed(const QString& filePath);

  void openImportDialog();
  void openExportDialog();
  void openQueryDialog();
  void onRemoveAction();

  void suspendModel();
  void resumeModel();
  void resetModel();

  /// Import a directory - this is used when the user selects a directory
  /// from the Import Dialog, but can also be used externally to trigger
  /// an import (i.e. for testing or to support drag-and-drop)
  void onImportDirectory(QString directory);

  /// slots to capture status updates from the database during an 
  /// import operation
  void onPatientAdded(int, QString, QString, QString);
  void onStudyAdded(QString);
  void onSeriesAdded(QString);
  void onInstanceAdded(QString);

Q_SIGNALS:
  /// Emited when directory is changed
  void databaseDirectoryChanged(const QString&);
  /// Emited when query/retrieve operation has happened
  void queryRetrieveFinished();
  /// Emited when the directory import operation has completed
  void directoryImported();

protected:
    QScopedPointer<ctkDICOMBrowserPrivate> d_ptr;
protected Q_SLOTS:
    void onModelSelected(const QModelIndex& index);

    /// To be called when a thumbnail in thumbnail list widget is selected
    void onThumbnailSelected(const ctkThumbnailLabel& widget);

    /// To be called when a thumbnail in thumbnail list widget is double-clicked
    void onThumbnailDoubleClicked(const ctkThumbnailLabel& widget);

    /// To be called when previous and next buttons are clicked
    void onNextImage();
    void onPreviousImage();
    void onNextSeries();
    void onPreviousSeries();
    void onNextStudy();
    void onPreviousStudy();
    /// To be called when dialog finishes
    void onQueryRetrieveFinished();

    /// To be called when an entry of the tree list is collapsed
    void onTreeCollapsed(const QModelIndex& index);

    /// To be called when an entry of the tree list is expanded
    void onTreeExpanded(const QModelIndex& index);

    /// To be called when auto-play checkbox state changed
    void onAutoPlayCheckboxStateChanged(int state);

    /// Called by timer for auto-play functionality
    void onAutoPlayTimer();

    /// To be called when the value of thumbnail size slider bar is changed
    void onThumbnailWidthSliderValueChanged(int val);

    /// To be called when search parameters in query widget changed
    void onSearchParameterChanged();

    /// To be called after image preview displayed an image
    void onImagePreviewDisplayed(int imageID, int count);

private Q_SLOTS:

    void onSearchPopUpButtonClicked();

    void onSearchWidgetTopLevelChanged(bool topLevel);

private:
  Q_DECLARE_PRIVATE(ctkDICOMBrowser);
  Q_DISABLE_COPY(ctkDICOMBrowser);
};

#endif
