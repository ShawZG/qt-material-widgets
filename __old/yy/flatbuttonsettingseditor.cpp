#include "yy/flatbuttonsettingseditor.h"
#include <QColorDialog>
#include "xx/qtmaterialflatbutton.h"

FlatButtonSettingsEditor::FlatButtonSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::FlatButtonSettingsForm),
      m_button(new QtMaterialFlatButton("I'm flat"))
{
    init();
}

FlatButtonSettingsEditor::~FlatButtonSettingsEditor()
{
    delete ui;
}

FlatButtonSettingsEditor::FlatButtonSettingsEditor(QtMaterialFlatButton *button, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::FlatButtonSettingsForm),
      m_button(button)
{
    init();
}

void FlatButtonSettingsEditor::setupForm()
{
    switch (m_button->role())
    {
    case XXMaterial::Default:
        ui->buttonRoleComboBox->setCurrentIndex(0);
        break;
    case XXMaterial::Primary:
        ui->buttonRoleComboBox->setCurrentIndex(1);
        break;
    case XXMaterial::Secondary:
        ui->buttonRoleComboBox->setCurrentIndex(2);
        break;
    default:
        break;
    }

    switch (m_button->overlayStyle())
    {
    case XXMaterial::NoOverlay:
        ui->hoverStyleComboBox->setCurrentIndex(0);
        break;
    case XXMaterial::TintedOverlay:
        ui->hoverStyleComboBox->setCurrentIndex(1);
        break;
    case XXMaterial::GrayOverlay:
        ui->hoverStyleComboBox->setCurrentIndex(2);
        break;
    default:
        break;
    }

    switch (m_button->rippleStyle())
    {
    case XXMaterial::CenteredRipple:
        ui->rippleStyleComboBox->setCurrentIndex(0);
        break;
    case XXMaterial::PositionedRipple:
        ui->rippleStyleComboBox->setCurrentIndex(1);
        break;
    case XXMaterial::NoRipple:
        ui->rippleStyleComboBox->setCurrentIndex(2);
        break;
    default:
        break;
    }

    switch (m_button->iconPlacement())
    {
    case XXMaterial::LeftIcon:
        ui->iconPlacementComboBox->setCurrentIndex(0);
        break;
    case XXMaterial::RightIcon:
        ui->iconPlacementComboBox->setCurrentIndex(1);
        break;
    }

    ui->checkedCheckBox->setEnabled(m_button->isCheckable());

    ui->disabledCheckBox->setChecked(!m_button->isEnabled());
    ui->checkableCheckBox->setChecked(m_button->isCheckable());
    ui->checkedCheckBox->setChecked(m_button->isChecked());
    ui->showHaloCheckBox->setChecked(m_button->isHaloVisible());
    ui->iconCheckBox->setChecked(!m_button->icon().isNull());
    ui->useThemeColorsCheckBox->setChecked(m_button->useThemeColors());
    ui->transparentCheckBox->setChecked(Qt::TransparentMode == m_button->backgroundMode());
    ui->cornerRadiusSpinBox->setValue(m_button->cornerRadius());
    ui->overlayOpacityDoubleSpinBox->setValue(m_button->baseOpacity());
    ui->iconSizeSpinBox->setValue(m_button->iconSize().width());
    ui->fontSizeDoubleSpinBox->setValue(m_button->fontSize());
    ui->buttonTextLineEdit->setText(m_button->text());
}

void FlatButtonSettingsEditor::updateWidget()
{
    switch (ui->buttonRoleComboBox->currentIndex())
    {
    case 0:
        m_button->setRole(XXMaterial::Default);
        break;
    case 1:
        m_button->setRole(XXMaterial::Primary);
        break;
    case 2:
        m_button->setRole(XXMaterial::Secondary);
        break;
    default:
        break;
    }

    switch (ui->hoverStyleComboBox->currentIndex())
    {
    case 0:
        m_button->setOverlayStyle(XXMaterial::NoOverlay);
        break;
    case 1:
        m_button->setOverlayStyle(XXMaterial::TintedOverlay);
        break;
    case 2:
        m_button->setOverlayStyle(XXMaterial::GrayOverlay);
        break;
    default:
        break;
    }

    switch (ui->rippleStyleComboBox->currentIndex())
    {
    case 0:
        m_button->setRippleStyle(XXMaterial::CenteredRipple);
        break;
    case 1:
        m_button->setRippleStyle(XXMaterial::PositionedRipple);
        break;
    case 2:
        m_button->setRippleStyle(XXMaterial::NoRipple);
        break;
    default:
        break;
    }

    switch (ui->iconPlacementComboBox->currentIndex())
    {
    case 0:
        m_button->setIconPlacement(XXMaterial::LeftIcon);
        break;
    case 1:
        m_button->setIconPlacement(XXMaterial::RightIcon);
        break;
    default:
        break;
    }

    m_button->setDisabled(ui->disabledCheckBox->isChecked());
    m_button->setCheckable(ui->checkableCheckBox->isChecked());
    m_button->setChecked(ui->checkedCheckBox->isChecked());
    m_button->setHaloVisible(ui->showHaloCheckBox->isChecked());
    m_button->setIcon(ui->iconCheckBox->isChecked() ? QIcon("../qt-material-widgets/ic_star_black_24px.svg")
                                                    : QIcon());
    m_button->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_button->setBackgroundMode(ui->transparentCheckBox->isChecked()
                                ? Qt::TransparentMode : Qt::OpaqueMode);
    m_button->setCornerRadius(ui->cornerRadiusSpinBox->value());
    m_button->setBaseOpacity(ui->overlayOpacityDoubleSpinBox->value());
    m_button->setIconSize(QSize(ui->iconSizeSpinBox->value(), ui->iconSizeSpinBox->value()));
    m_button->setFontSize(ui->fontSizeDoubleSpinBox->value());
    m_button->setText(ui->buttonTextLineEdit->text());

    ui->checkedCheckBox->setEnabled(m_button->isCheckable());
}

void FlatButtonSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("foregroundColorToolButton" == senderName) {
            m_button->setForegroundColor(color);
            ui->foregroundColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("backgroundColorToolButton" == senderName) {
            m_button->setBackgroundColor(color);
            ui->backgroundColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("overlayColorToolButton" == senderName) {
            m_button->setOverlayColor(color);
            ui->overlayColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("disabledFgColorToolButton" == senderName) {
            m_button->setDisabledForegroundColor(color);
            ui->disableFgColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("disabledBgColorToolButton" == senderName) {
            m_button->setDisabledBackgroundColor(color);
            ui->disabledBgColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}

void FlatButtonSettingsEditor::applyDefaultPreset()
{
    m_button->setRole(XXMaterial::Default);
    m_button->setRippleStyle(XXMaterial::PositionedRipple);
    m_button->setIconPlacement(XXMaterial::LeftIcon);
    m_button->setOverlayStyle(XXMaterial::GrayOverlay);
    m_button->setBackgroundMode(Qt::TransparentMode);
    m_button->setCornerRadius(3);
    m_button->setBaseOpacity(0.13);
    m_button->setFontSize(10);
    m_button->setUseThemeColors(true);
    m_button->setHaloVisible(true);
    m_button->setCheckable(false);
    m_button->setEnabled(true);
    m_button->applyPreset(XXMaterial::FlatPreset);
    setupForm();
}

void FlatButtonSettingsEditor::applyCheckablePreset()
{
    m_button->setRole(XXMaterial::Default);
    m_button->setRippleStyle(XXMaterial::PositionedRipple);
    m_button->setIconPlacement(XXMaterial::LeftIcon);
    m_button->setOverlayStyle(XXMaterial::GrayOverlay);
    m_button->setBackgroundMode(Qt::TransparentMode);
    m_button->setCornerRadius(3);
    m_button->setBaseOpacity(0.13);
    m_button->setFontSize(10);
    m_button->setUseThemeColors(true);
    m_button->setHaloVisible(true);
    m_button->setCheckable(true);
    m_button->setEnabled(true);
    m_button->applyPreset(XXMaterial::CheckablePreset);
    setupForm();
}

void FlatButtonSettingsEditor::init()
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    ui->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);

    m_button->setFixedWidth(300);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);
    layout->addWidget(m_button);
    layout->setAlignment(m_button, Qt::AlignCenter);

    setupForm();

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->checkableCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->checkedCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->showHaloCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->iconCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->transparentCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->buttonRoleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->rippleStyleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->hoverStyleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->iconPlacementComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->cornerRadiusSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->overlayOpacityDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidget()));
    connect(ui->iconSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->fontSizeDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidget()));
    connect(ui->buttonTextLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->foregroundColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->backgroundColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->disabledFgColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->disabledBgColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->overlayColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->cornerRadiusSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->overlayOpacityDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidget()));
    connect(ui->iconSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->fontSizeDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidget()));
    connect(ui->buttonTextLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui->defaultPresetPushButton, SIGNAL(pressed()), this, SLOT(applyDefaultPreset()));
    connect(ui->checkablePresetPushButton, SIGNAL(pressed()), this, SLOT(applyCheckablePreset()));
    connect(m_button, SIGNAL(toggled(bool)), this, SLOT(setupForm()));
}

