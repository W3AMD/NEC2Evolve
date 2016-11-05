object DesignForm: TDesignForm
  Left = 0
  Top = 0
  Caption = 'Design Entry'
  ClientHeight = 473
  ClientWidth = 523
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object BitBtn1: TBitBtn
    Left = 334
    Top = 431
    Width = 75
    Height = 25
    Kind = bkOK
    NumGlyphs = 2
    TabOrder = 0
  end
  object BitBtn2: TBitBtn
    Left = 430
    Top = 431
    Width = 75
    Height = 25
    Kind = bkCancel
    NumGlyphs = 2
    TabOrder = 1
  end
  object GroupBox1: TGroupBox
    Left = 191
    Top = 8
    Width = 121
    Height = 353
    Caption = 'Band List (Meters)'
    Enabled = False
    TabOrder = 2
    Visible = False
    object Band160: TCheckBox
      Left = 16
      Top = 24
      Width = 41
      Height = 17
      Caption = '160'
      Enabled = False
      TabOrder = 0
    end
    object Band80: TCheckBox
      Left = 16
      Top = 48
      Width = 41
      Height = 17
      Caption = '80'
      Enabled = False
      TabOrder = 1
    end
    object Band60: TCheckBox
      Left = 16
      Top = 71
      Width = 41
      Height = 17
      Caption = '60'
      Enabled = False
      TabOrder = 2
    end
    object Band40: TCheckBox
      Left = 16
      Top = 96
      Width = 41
      Height = 17
      Caption = '40'
      Enabled = False
      TabOrder = 3
    end
    object Band30: TCheckBox
      Left = 16
      Top = 120
      Width = 41
      Height = 17
      Caption = '30'
      Enabled = False
      TabOrder = 4
    end
    object Band20: TCheckBox
      Left = 16
      Top = 143
      Width = 41
      Height = 17
      Caption = '20'
      Enabled = False
      TabOrder = 5
    end
    object Band17: TCheckBox
      Left = 16
      Top = 168
      Width = 41
      Height = 17
      Caption = '17'
      Enabled = False
      TabOrder = 6
    end
    object Band15: TCheckBox
      Left = 16
      Top = 192
      Width = 41
      Height = 17
      Caption = '15'
      Enabled = False
      TabOrder = 7
    end
    object Band10: TCheckBox
      Left = 16
      Top = 215
      Width = 41
      Height = 17
      Caption = '10'
      Enabled = False
      TabOrder = 8
    end
    object Band6: TCheckBox
      Left = 16
      Top = 240
      Width = 41
      Height = 17
      Caption = '6'
      Enabled = False
      TabOrder = 9
    end
    object Band2: TCheckBox
      Left = 16
      Top = 264
      Width = 41
      Height = 17
      Caption = '2'
      Checked = True
      State = cbChecked
      TabOrder = 10
    end
    object Band1: TCheckBox
      Left = 16
      Top = 287
      Width = 41
      Height = 17
      Caption = '1'
      Enabled = False
      TabOrder = 11
    end
    object Band70cm: TCheckBox
      Left = 16
      Top = 310
      Width = 49
      Height = 17
      Caption = '70 cm'
      Enabled = False
      TabOrder = 12
    end
  end
  object AntennaType: TRadioGroup
    Left = 8
    Top = 8
    Width = 177
    Height = 186
    Caption = 'Antenna Type'
    Enabled = False
    ItemIndex = 0
    Items.Strings = (
      'Dipole (symetrical)')
    TabOrder = 3
  end
  object SupportPoints: TGroupBox
    Left = 318
    Top = 8
    Width = 187
    Height = 417
    Caption = 'Support Points'
    TabOrder = 4
    object Label1: TLabel
      Left = 24
      Top = 25
      Width = 102
      Height = 13
      Caption = 'Number Of Supports:'
    end
    object MaxHeightLB: TLabel
      Left = 18
      Top = 173
      Width = 106
      Height = 13
      Caption = 'Maximum Height (cm):'
    end
    object MaxYardSizeLB: TLabel
      Left = 16
      Top = 272
      Width = 118
      Height = 13
      Caption = 'Max Yard Size (cm; x,y):'
    end
    object MinimumHeightLB: TLabel
      Left = 16
      Top = 219
      Width = 102
      Height = 13
      Caption = 'Minimum Height (cm):'
    end
    object FeedPointHeightLB: TLabel
      Left = 16
      Top = 345
      Width = 113
      Height = 13
      Caption = 'Feed Point Height: (cm)'
    end
    object NumberSupports: TEdit
      Left = 24
      Top = 44
      Width = 62
      Height = 21
      Enabled = False
      TabOrder = 0
      Text = '3'
    end
    object MaxSupports: TUpDown
      Left = 86
      Top = 44
      Width = 16
      Height = 21
      Associate = NumberSupports
      Enabled = False
      Min = 1
      Max = 3
      Position = 3
      TabOrder = 1
    end
    object RadioGroup1: TRadioGroup
      Left = 16
      Top = 71
      Width = 153
      Height = 86
      Caption = 'Support Adjustment'
      Enabled = False
      ItemIndex = 2
      Items.Strings = (
        'None'
        'Height'
        'Height && Position')
      TabOrder = 2
    end
    object Edit1: TEdit
      Left = 18
      Top = 192
      Width = 62
      Height = 21
      TabOrder = 3
      Text = '370'
    end
    object MaxHeight: TUpDown
      Left = 80
      Top = 192
      Width = 16
      Height = 21
      Associate = Edit1
      Min = 1
      Max = 100000
      Position = 370
      TabOrder = 4
    end
    object Edit2: TEdit
      Left = 16
      Top = 291
      Width = 65
      Height = 21
      TabOrder = 5
      Text = '70'
    end
    object MaxXSize: TUpDown
      Left = 81
      Top = 291
      Width = 16
      Height = 21
      Associate = Edit2
      Max = 100000
      Position = 70
      TabOrder = 6
    end
    object Edit3: TEdit
      Left = 16
      Top = 318
      Width = 65
      Height = 21
      TabOrder = 7
      Text = '0'
    end
    object MaxYSize: TUpDown
      Left = 81
      Top = 318
      Width = 16
      Height = 21
      Associate = Edit3
      Max = 100000
      TabOrder = 8
    end
    object Edit4: TEdit
      Left = 18
      Top = 238
      Width = 62
      Height = 21
      TabOrder = 9
      Text = '300'
    end
    object MinHeight: TUpDown
      Left = 80
      Top = 238
      Width = 16
      Height = 21
      Associate = Edit4
      Max = 100000
      Position = 300
      TabOrder = 10
    end
    object FeedHeight: TUpDown
      Left = 81
      Top = 363
      Width = 16
      Height = 21
      Associate = Edit5
      Max = 100000
      Position = 300
      TabOrder = 11
    end
    object Edit5: TEdit
      Left = 16
      Top = 363
      Width = 65
      Height = 21
      TabOrder = 12
      Text = '300'
    end
  end
  object TunerOptions: TRadioGroup
    Left = 8
    Top = 194
    Width = 177
    Height = 153
    Caption = 'Tuner Options'
    Enabled = False
    ItemIndex = 0
    Items.Strings = (
      'None (SWR < 2)'
      'Built in tuner (SWR<3)'
      'Additional tuner (SWR <10)'
      'Wet noodle tuner (SWR <100)')
    TabOrder = 5
  end
  object BandList: TRadioGroup
    Left = 191
    Top = 8
    Width = 121
    Height = 343
    Caption = 'Band List (Meters)'
    Items.Strings = (
      '160'
      '80'
      '60'
      '40'
      '30'
      '20'
      '17'
      '15'
      '12'
      '10'
      '6'
      '2'
      '1.25'
      '70 cm'
      '33 cm'
      '23 cm')
    TabOrder = 6
    OnClick = BandListClick
  end
  object NoStraysAllowed: TCheckBox
    Left = 8
    Top = 368
    Width = 121
    Height = 17
    Caption = 'No Strays Allowed'
    Checked = True
    State = cbChecked
    TabOrder = 7
    Visible = False
  end
end
