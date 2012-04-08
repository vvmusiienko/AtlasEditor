object Form1: TForm1
  Left = 142
  Top = 108
  Width = 924
  Height = 686
  Caption = 'MuHAOS Atlas Editor'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  DesignSize = (
    916
    639)
  PixelsPerInch = 96
  TextHeight = 13
  object Image2: TImage
    Left = 110
    Top = 85
    Width = 512
    Height = 512
    Stretch = True
  end
  object PaintBox1: TPaintBox
    Left = 110
    Top = 85
    Width = 301
    Height = 236
    OnMouseDown = PaintBox1MouseDown
    OnMouseMove = PaintBox1MouseMove
    OnMouseUp = PaintBox1MouseUp
    OnPaint = PaintBox1Paint
  end
  object AddButton: TSpeedButton
    Left = 5
    Top = 589
    Width = 101
    Height = 16
    Anchors = [akLeft, akBottom]
    Caption = 'Add'
    OnClick = AddButtonClick
  end
  object DeleteButton: TSpeedButton
    Left = 5
    Top = 604
    Width = 101
    Height = 16
    Anchors = [akLeft, akBottom]
    Caption = 'Delete'
    OnClick = DeleteButtonClick
  end
  object ListBox1: TListBox
    Left = 5
    Top = 5
    Width = 101
    Height = 575
    Anchors = [akLeft, akTop, akBottom]
    ItemHeight = 13
    TabOrder = 0
    OnClick = ListBox1Click
  end
  object GroupBox2: TGroupBox
    Left = 110
    Top = 0
    Width = 410
    Height = 81
    Caption = 'Character'
    TabOrder = 1
    object Label4: TLabel
      Left = 15
      Top = 20
      Width = 8
      Height = 13
      Caption = 'U'
    end
    object Label5: TLabel
      Left = 15
      Top = 45
      Width = 7
      Height = 13
      Caption = 'V'
    end
    object Label6: TLabel
      Left = 135
      Top = 45
      Width = 15
      Height = 13
      Caption = 'VH'
    end
    object Label7: TLabel
      Left = 135
      Top = 20
      Width = 16
      Height = 13
      Caption = 'UH'
    end
    object SpeedButton1: TSpeedButton
      Left = 355
      Top = 15
      Width = 46
      Height = 17
      Caption = 'Copy'
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 355
      Top = 35
      Width = 46
      Height = 17
      Caption = 'Paste'
      OnClick = SpeedButton2Click
    end
    object Edit1: TEdit
      Left = 35
      Top = 20
      Width = 71
      Height = 21
      TabOrder = 0
      Text = '0'
      OnKeyDown = Edit1KeyDown
    end
    object Edit2: TEdit
      Left = 35
      Top = 45
      Width = 71
      Height = 21
      TabOrder = 1
      Text = '0'
      OnKeyDown = Edit1KeyDown
    end
    object Edit3: TEdit
      Left = 155
      Top = 20
      Width = 71
      Height = 21
      TabOrder = 2
      Text = '0'
      OnKeyDown = Edit1KeyDown
    end
    object Edit4: TEdit
      Left = 155
      Top = 45
      Width = 71
      Height = 21
      TabOrder = 3
      Text = '0'
      OnKeyDown = Edit1KeyDown
    end
    object RadioGroup1: TRadioGroup
      Left = 235
      Top = 15
      Width = 111
      Height = 56
      Caption = 'Positioning'
      ItemIndex = 0
      Items.Strings = (
        'Relative'
        'Pixels')
      TabOrder = 4
      OnClick = RadioGroup1Click
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 620
    Width = 916
    Height = 19
    Panels = <
      item
        Text = 'Texture Width'
        Width = 150
      end
      item
        Text = 'Texture Height'
        Width = 150
      end
      item
        Text = 'Chars Range'
        Width = 150
      end
      item
        Text = 'Texture Type'
        Width = 150
      end>
    SimplePanel = False
  end
  object GroupBox1: TGroupBox
    Left = 520
    Top = 0
    Width = 393
    Height = 81
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Other'
    TabOrder = 3
    object Label1: TLabel
      Left = 15
      Top = 20
      Width = 27
      Height = 13
      Caption = 'Zoom'
    end
    object Label2: TLabel
      Left = 15
      Top = 45
      Width = 48
      Height = 13
      Caption = 'Edit Mode'
    end
    object ComboBox1: TComboBox
      Left = 70
      Top = 20
      Width = 106
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 0
      Text = '1X'
      OnChange = ComboBox1Change
      Items.Strings = (
        '1X'
        '2X')
    end
    object ComboBox2: TComboBox
      Left = 70
      Top = 45
      Width = 106
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 1
      Text = 'Sizing'
      OnChange = ComboBox1Change
      Items.Strings = (
        'Sizing'
        'Moving')
    end
    object GroupBox3: TGroupBox
      Left = 180
      Top = 10
      Width = 206
      Height = 66
      Caption = 'Texture Size'
      TabOrder = 2
      object Label3: TLabel
        Left = 5
        Top = 15
        Width = 28
        Height = 13
        Caption = 'Width'
      end
      object Label8: TLabel
        Left = 5
        Top = 35
        Width = 31
        Height = 13
        Caption = 'Height'
      end
      object ApplySize: TSpeedButton
        Left = 130
        Top = 15
        Width = 66
        Height = 41
        Caption = 'Apply'
        OnClick = ApplySizeClick
      end
      object Edit5: TEdit
        Left = 55
        Top = 15
        Width = 66
        Height = 21
        TabOrder = 0
        Text = '0'
      end
      object Edit6: TEdit
        Left = 55
        Top = 35
        Width = 66
        Height = 21
        TabOrder = 1
        Text = '0'
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 465
    Top = 490
    object File1: TMenuItem
      Caption = 'File'
      object Open1: TMenuItem
        Caption = 'Open'
        OnClick = Open1Click
      end
      object Save1: TMenuItem
        Caption = 'Save'
        OnClick = Save1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
    object Image1: TMenuItem
      Caption = 'Image'
      object Load1: TMenuItem
        Caption = 'Load'
        OnClick = Load1Click
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Atlas File|*.atl'
    Left = 680
    Top = 435
  end
  object SaveDialog1: TSaveDialog
    Left = 645
    Top = 435
  end
  object SaveDialog2: TSaveDialog
    Filter = 'TGA Image|*.tga'
    Left = 645
    Top = 490
  end
  object OpenDialog2: TOpenDialog
    Left = 680
    Top = 490
  end
end
