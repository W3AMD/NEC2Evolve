object Form1: TForm1
  Left = 411
  Top = 338
  Width = 1208
  Height = 795
  AutoScroll = True
  Caption = 'NECEvolve Alpha Development Version 0.1.7'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StatusCaption: TLabel
    Left = 10
    Top = 726
    Width = 31
    Height = 13
    Caption = 'Status'
  end
  object Label2: TLabel
    Left = 9
    Top = 112
    Width = 87
    Height = 13
    Caption = 'Max Total Gain:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 17
    Top = 131
    Width = 50
    Height = 13
    Caption = 'Gain (dBi):'
  end
  object Label4: TLabel
    Left = 17
    Top = 150
    Width = 47
    Height = 13
    Caption = 'Phi (deg):'
  end
  object Label5: TLabel
    Left = 17
    Top = 169
    Width = 61
    Height = 13
    Caption = 'Theta (deg):'
  end
  object TotalGaindBLabel: TLabel
    Left = 73
    Top = 131
    Width = 6
    Height = 13
    Caption = '0'
  end
  object TotalGainPhiLabel: TLabel
    Left = 73
    Top = 150
    Width = 6
    Height = 13
    Caption = '0'
  end
  object TotalGainThetaLabel: TLabel
    Left = 84
    Top = 169
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label6: TLabel
    Left = 10
    Top = 192
    Width = 101
    Height = 13
    Caption = 'Max Vertical Gain:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label7: TLabel
    Left = 17
    Top = 211
    Width = 50
    Height = 13
    Caption = 'Gain (dBi):'
  end
  object Label8: TLabel
    Left = 17
    Top = 230
    Width = 47
    Height = 13
    Caption = 'Phi (deg):'
  end
  object Label9: TLabel
    Left = 17
    Top = 249
    Width = 61
    Height = 13
    Caption = 'Theta (deg):'
  end
  object VertGaindBLabel: TLabel
    Left = 74
    Top = 211
    Width = 6
    Height = 13
    Caption = '0'
  end
  object VertPhiLabel: TLabel
    Left = 74
    Top = 230
    Width = 6
    Height = 13
    Caption = '0'
  end
  object VertThetaLabel: TLabel
    Left = 85
    Top = 249
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label10: TLabel
    Left = 12
    Top = 278
    Width = 116
    Height = 13
    Caption = 'Max Horizontal Gain:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label11: TLabel
    Left = 19
    Top = 297
    Width = 50
    Height = 13
    Caption = 'Gain (dBi):'
  end
  object Label12: TLabel
    Left = 19
    Top = 316
    Width = 47
    Height = 13
    Caption = 'Phi (deg):'
  end
  object Label13: TLabel
    Left = 19
    Top = 335
    Width = 61
    Height = 13
    Caption = 'Theta (deg):'
  end
  object HorzGaindBLabel: TLabel
    Left = 76
    Top = 297
    Width = 6
    Height = 13
    Caption = '0'
  end
  object HorzPhiLabel: TLabel
    Left = 76
    Top = 316
    Width = 6
    Height = 13
    Caption = '0'
  end
  object HorzThetaLabel: TLabel
    Left = 87
    Top = 335
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label14: TLabel
    Left = 9
    Top = 360
    Width = 121
    Height = 13
    Caption = 'Antenna Parameters:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label15: TLabel
    Left = 19
    Top = 433
    Width = 33
    Height = 13
    Caption = 'VSWR:'
  end
  object VSWRLabel: TLabel
    Left = 58
    Top = 433
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label16: TLabel
    Left = 19
    Top = 414
    Width = 10
    Height = 13
    Caption = 'X:'
  end
  object XLabel: TLabel
    Left = 36
    Top = 414
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label18: TLabel
    Left = 19
    Top = 395
    Width = 11
    Height = 13
    Caption = 'R:'
  end
  object RLabel: TLabel
    Left = 36
    Top = 395
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label17: TLabel
    Left = 19
    Top = 379
    Width = 86
    Height = 13
    Caption = 'Frequency (MHz):'
  end
  object FreqLabel: TLabel
    Left = 111
    Top = 379
    Width = 6
    Height = 13
    Caption = '0'
  end
  object OptMode: TLabel
    Left = 8
    Top = 452
    Width = 44
    Height = 13
    Caption = 'OptMode'
  end
  object Label19: TLabel
    Left = 8
    Top = 488
    Width = 76
    Height = 13
    Caption = 'Enable Vec Cnt:'
  end
  object Label20: TLabel
    Left = 8
    Top = 507
    Width = 78
    Height = 13
    Caption = 'Disable Vec Cnt:'
  end
  object EnableVectorCountLB: TLabel
    Left = 96
    Top = 488
    Width = 6
    Height = 13
    Caption = '0'
  end
  object DisableVectorCountLB: TLabel
    Left = 96
    Top = 507
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label21: TLabel
    Left = 8
    Top = 526
    Width = 60
    Height = 13
    Caption = 'Total Count:'
  end
  object TotalCount: TLabel
    Left = 80
    Top = 526
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label22: TLabel
    Left = 8
    Top = 545
    Width = 62
    Height = 13
    Caption = 'SWR Target:'
  end
  object Label23: TLabel
    Left = 8
    Top = 560
    Width = 85
    Height = 13
    Caption = 'Horz Gain Target:'
  end
  object SWRTarget: TLabel
    Left = 80
    Top = 545
    Width = 6
    Height = 13
    Caption = '0'
  end
  object HorzGainTarget: TLabel
    Left = 104
    Top = 560
    Width = 6
    Height = 13
    Caption = '0'
  end
  object OptimizationMode: TLabel
    Left = 8
    Top = 578
    Width = 25
    Height = 13
    Caption = 'None'
  end
  object Label24: TLabel
    Left = 8
    Top = 597
    Width = 72
    Height = 13
    Caption = 'Enabled Wires:'
  end
  object Label25: TLabel
    Left = 8
    Top = 616
    Width = 74
    Height = 13
    Caption = 'Disabled Wires:'
  end
  object EnabledWireCountLB: TLabel
    Left = 88
    Top = 597
    Width = 6
    Height = 13
    Caption = '0'
  end
  object DisabledWireCountLB: TLabel
    Left = 88
    Top = 616
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label1: TLabel
    Left = 51
    Top = 675
    Width = 3
    Height = 13
  end
  object Label26: TLabel
    Left = 8
    Top = 472
    Width = 66
    Height = 13
    Caption = 'Current Wire:'
  end
  object EnableWireLB: TLabel
    Left = 88
    Top = 472
    Width = 3
    Height = 13
  end
  object Label27: TLabel
    Left = 8
    Top = 635
    Width = 72
    Height = 13
    Caption = 'Ignored Wires:'
  end
  object IgnoredWireCountLB: TLabel
    Left = 100
    Top = 635
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label28: TLabel
    Left = 8
    Top = 654
    Width = 72
    Height = 13
    Caption = 'Enabled Wires:'
  end
  object EnabledVWireCountLB: TLabel
    Left = 100
    Top = 654
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label30: TLabel
    Left = 8
    Top = 673
    Width = 74
    Height = 13
    Caption = 'Disabled Wires:'
  end
  object DisabledVWireCountLB: TLabel
    Left = 99
    Top = 673
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label29: TLabel
    Left = 8
    Top = 694
    Width = 61
    Height = 13
    Caption = 'SWR vector:'
  end
  object SWRVectorLB: TLabel
    Left = 99
    Top = 694
    Width = 6
    Height = 13
    Caption = '0'
  end
  object EnabledListLB: TLabel
    Left = 607
    Top = 635
    Width = 553
    Height = 32
    AutoSize = False
    WordWrap = True
  end
  object IgnoredListLB: TLabel
    Left = 607
    Top = 673
    Width = 553
    Height = 34
    AutoSize = False
    WordWrap = True
  end
  object SWRListLB: TLabel
    Left = 607
    Top = 714
    Width = 553
    Height = 34
    AutoSize = False
    WordWrap = True
  end
  object Open: TButton
    Left = 8
    Top = 47
    Width = 75
    Height = 25
    Caption = 'Open'
    TabOrder = 0
    OnClick = OpenClick
  end
  object Chart1: TChart
    Left = 607
    Top = 214
    Width = 275
    Height = 200
    BackWall.Brush.Gradient.Direction = gdBottomTop
    BackWall.Brush.Gradient.EndColor = clWhite
    BackWall.Brush.Gradient.StartColor = 15395562
    BackWall.Brush.Gradient.Visible = True
    Foot.Font.Color = clBlue
    Foot.Font.Name = 'Verdana'
    Gradient.Direction = gdBottomTop
    Gradient.EndColor = clWhite
    Gradient.MidColor = 15395562
    Gradient.StartColor = 15395562
    Gradient.Visible = True
    LeftWall.Color = 14745599
    Legend.Font.Name = 'Verdana'
    Legend.LegendStyle = lsSeries
    Legend.Shadow.Transparency = 0
    Legend.Visible = False
    RightWall.Color = 14745599
    Title.Font.Name = 'Verdana'
    Title.Text.Strings = (
      'Verticle Gain (dBi) - Top View')
    AxisBehind = False
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.Increment = 30.000000000000000000
    BottomAxis.LabelsFormat.Font.Name = 'Verdana'
    BottomAxis.MinimumRound = True
    BottomAxis.TicksInner.Color = 11119017
    BottomAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Axis.Color = 4210752
    DepthAxis.Grid.Color = 11119017
    DepthAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthAxis.TicksInner.Color = 11119017
    DepthAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Visible = True
    DepthTopAxis.Axis.Color = 4210752
    DepthTopAxis.Grid.Color = 11119017
    DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthTopAxis.TicksInner.Color = 11119017
    DepthTopAxis.Title.Font.Name = 'Verdana'
    DepthTopAxis.Visible = True
    LeftAxis.Axis.Color = 4210752
    LeftAxis.Grid.Color = 11119017
    LeftAxis.LabelsFormat.Font.Name = 'Verdana'
    LeftAxis.MaximumRound = True
    LeftAxis.MinimumRound = True
    LeftAxis.TicksInner.Color = 11119017
    LeftAxis.Title.Font.Name = 'Verdana'
    RightAxis.Axis.Color = 4210752
    RightAxis.Grid.Color = 11119017
    RightAxis.LabelsFormat.Font.Name = 'Verdana'
    RightAxis.MinimumRound = True
    RightAxis.TicksInner.Color = 11119017
    RightAxis.Title.Font.Name = 'Verdana'
    RightAxis.ZPosition = 0.010000000000000000
    TopAxis.Axis.Color = 4210752
    TopAxis.Grid.Color = 11119017
    TopAxis.LabelsFormat.Font.Name = 'Verdana'
    TopAxis.MinimumRound = True
    TopAxis.TicksInner.Color = 11119017
    TopAxis.Title.Font.Name = 'Verdana'
    TopAxis.ZPosition = 0.010000000000000000
    View3D = False
    Zoom.KeepAspectRatio = True
    TabOrder = 1
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
    object Series1: TPolarSeries
      Title = 'Vertical'
      XValues.Name = 'Angle'
      XValues.Order = loNone
      YValues.Name = 'Radius'
      YValues.Order = loNone
      Frame.InnerBrush.BackColor = clRed
      Frame.InnerBrush.Gradient.EndColor = clGray
      Frame.InnerBrush.Gradient.MidColor = clWhite
      Frame.InnerBrush.Gradient.StartColor = 4210752
      Frame.InnerBrush.Gradient.Visible = True
      Frame.MiddleBrush.BackColor = clYellow
      Frame.MiddleBrush.Gradient.EndColor = 8553090
      Frame.MiddleBrush.Gradient.MidColor = clWhite
      Frame.MiddleBrush.Gradient.StartColor = clGray
      Frame.MiddleBrush.Gradient.Visible = True
      Frame.OuterBrush.BackColor = clGreen
      Frame.OuterBrush.Gradient.EndColor = 4210752
      Frame.OuterBrush.Gradient.MidColor = clWhite
      Frame.OuterBrush.Gradient.StartColor = clSilver
      Frame.OuterBrush.Gradient.Visible = True
      Frame.Width = 4
      Shadow.Visible = False
      AngleIncrement = 30.000000000000000000
      AngleValues.Name = 'AngleValues'
      AngleValues.Order = loAscending
      AngleLabels.ClockWise = True
      CloseCircle = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      RotationAngle = 90
      Data = {
        01170000000000000000888A400000000000888A40CDCCCCCCCCCC7340000000
        000000504000000000000050406666666666E672400000000000407F40000000
        0000407F400000000000007240000000000020644000000000002064409A9999
        9999197140000000000078804000000000007880403333333333337040000000
        0000C062400000000000C062409A99999999996E400000000000988E40000000
        0000988E40CDCCCCCCCCCC6C4000000000007884400000000000788440000000
        0000006B40000000000068864000000000006886403333333333336940000000
        0000D08A400000000000D08A4066666666666667400000000000C06140000000
        0000C06140999999999999654000000000009887400000000000988740CDCCCC
        CCCCCC6340000000000028804000000000002880400000000000006240000000
        0000088740000000000008874033333333333360400000000000788840000000
        0000788840CCCCCCCCCCCC5C400000000000807B400000000000807B40343333
        3333335940000000000048834000000000004883409899999999995540000000
        0000F08C400000000000F08C4000000000000052400000000000C08840000000
        0000C08840C8CCCCCCCCCC4C400000000000008C400000000000008C40989999
        999999454000000000004075400000000000407540D0CCCCCCCCCC3C40000000
        0000F088400000000000F08840C0CCCCCCCCCC2C400000000000C88140000000
        0000C881400000000000000000}
      Detail = {0000000000}
    end
  end
  object Chart2: TChart
    Left = 607
    Top = 419
    Width = 275
    Height = 200
    BackWall.Brush.Gradient.Direction = gdBottomTop
    BackWall.Brush.Gradient.EndColor = clWhite
    BackWall.Brush.Gradient.StartColor = 15395562
    BackWall.Brush.Gradient.Visible = True
    Foot.Font.Color = clBlue
    Foot.Font.Name = 'Verdana'
    Gradient.Direction = gdBottomTop
    Gradient.EndColor = clWhite
    Gradient.MidColor = 15395562
    Gradient.StartColor = 15395562
    Gradient.Visible = True
    LeftWall.Color = 14745599
    Legend.Font.Name = 'Verdana'
    Legend.LegendStyle = lsSeries
    Legend.Shadow.Transparency = 0
    Legend.Visible = False
    RightWall.Color = 14745599
    Title.Font.Name = 'Verdana'
    Title.Text.Strings = (
      'Horizontal Gain (dBi) - Top View')
    AxisBehind = False
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.Increment = 30.000000000000000000
    BottomAxis.LabelsFormat.Font.Name = 'Verdana'
    BottomAxis.MinimumRound = True
    BottomAxis.TicksInner.Color = 11119017
    BottomAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Axis.Color = 4210752
    DepthAxis.Grid.Color = 11119017
    DepthAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthAxis.MaximumOffset = 90
    DepthAxis.MinimumOffset = 90
    DepthAxis.TicksInner.Color = 11119017
    DepthAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Visible = True
    DepthTopAxis.Axis.Color = 4210752
    DepthTopAxis.Grid.Color = 11119017
    DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthTopAxis.MaximumOffset = 90
    DepthTopAxis.MinimumOffset = 90
    DepthTopAxis.TicksInner.Color = 11119017
    DepthTopAxis.Title.Font.Name = 'Verdana'
    DepthTopAxis.Visible = True
    LeftAxis.Axis.Color = 4210752
    LeftAxis.Grid.Color = 11119017
    LeftAxis.LabelsFormat.Font.Name = 'Verdana'
    LeftAxis.MinimumRound = True
    LeftAxis.TicksInner.Color = 11119017
    LeftAxis.Title.Font.Name = 'Verdana'
    RightAxis.Axis.Color = 4210752
    RightAxis.Grid.Color = 11119017
    RightAxis.LabelsFormat.Font.Name = 'Verdana'
    RightAxis.MinimumRound = True
    RightAxis.TicksInner.Color = 11119017
    RightAxis.Title.Font.Name = 'Verdana'
    RightAxis.ZPosition = 0.010000000000000000
    TopAxis.Axis.Color = 4210752
    TopAxis.Grid.Color = 11119017
    TopAxis.LabelsFormat.Font.Name = 'Verdana'
    TopAxis.MinimumRound = True
    TopAxis.TicksInner.Color = 11119017
    TopAxis.Title.Font.Name = 'Verdana'
    TopAxis.ZPosition = 0.010000000000000000
    View3D = False
    Zoom.KeepAspectRatio = True
    TabOrder = 2
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
    object PolarSeries1: TPolarSeries
      SeriesColor = 9192
      Title = 'Horizontal'
      XValues.Name = 'Angle'
      XValues.Order = loNone
      YValues.Name = 'Radius'
      YValues.Order = loNone
      Frame.InnerBrush.BackColor = clRed
      Frame.InnerBrush.Gradient.EndColor = clGray
      Frame.InnerBrush.Gradient.MidColor = clWhite
      Frame.InnerBrush.Gradient.StartColor = 4210752
      Frame.InnerBrush.Gradient.Visible = True
      Frame.MiddleBrush.BackColor = clYellow
      Frame.MiddleBrush.Gradient.EndColor = 8553090
      Frame.MiddleBrush.Gradient.MidColor = clWhite
      Frame.MiddleBrush.Gradient.StartColor = clGray
      Frame.MiddleBrush.Gradient.Visible = True
      Frame.OuterBrush.BackColor = clGreen
      Frame.OuterBrush.Gradient.EndColor = 4210752
      Frame.OuterBrush.Gradient.MidColor = clWhite
      Frame.OuterBrush.Gradient.StartColor = clSilver
      Frame.OuterBrush.Gradient.Visible = True
      Frame.Width = 4
      Shadow.Visible = False
      AngleIncrement = 30.000000000000000000
      AngleValues.Name = 'AngleValues'
      AngleValues.Order = loAscending
      AngleLabels.ClockWise = True
      CloseCircle = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      RotationAngle = 90
      Data = {
        01170000000000000000888A400000000000888A40CDCCCCCCCCCC7340000000
        000000504000000000000050406666666666E672400000000000407F40000000
        0000407F400000000000007240000000000020644000000000002064409A9999
        9999197140000000000078804000000000007880403333333333337040000000
        0000C062400000000000C062409A99999999996E400000000000988E40000000
        0000988E40CDCCCCCCCCCC6C4000000000007884400000000000788440000000
        0000006B40000000000068864000000000006886403333333333336940000000
        0000D08A400000000000D08A4066666666666667400000000000C06140000000
        0000C06140999999999999654000000000009887400000000000988740CDCCCC
        CCCCCC6340000000000028804000000000002880400000000000006240000000
        0000088740000000000008874033333333333360400000000000788840000000
        0000788840CCCCCCCCCCCC5C400000000000807B400000000000807B40343333
        3333335940000000000048834000000000004883409899999999995540000000
        0000F08C400000000000F08C4000000000000052400000000000C08840000000
        0000C08840C8CCCCCCCCCC4C400000000000008C400000000000008C40989999
        999999454000000000004075400000000000407540D0CCCCCCCCCC3C40000000
        0000F088400000000000F08840C0CCCCCCCCCC2C400000000000C88140000000
        0000C881400000000000000000}
      Detail = {0000000000}
    end
  end
  object Chart3: TChart
    Left = 607
    Top = 8
    Width = 275
    Height = 200
    BackWall.Brush.Gradient.Direction = gdBottomTop
    BackWall.Brush.Gradient.EndColor = clWhite
    BackWall.Brush.Gradient.StartColor = 15395562
    BackWall.Brush.Gradient.Visible = True
    Foot.Font.Color = clBlue
    Foot.Font.Name = 'Verdana'
    Gradient.Direction = gdBottomTop
    Gradient.EndColor = clWhite
    Gradient.MidColor = 15395562
    Gradient.StartColor = 15395562
    Gradient.Visible = True
    LeftWall.Color = 14745599
    Legend.Font.Name = 'Verdana'
    Legend.LegendStyle = lsSeries
    Legend.Shadow.Transparency = 0
    Legend.Visible = False
    RightWall.Color = 14745599
    Title.Font.Name = 'Verdana'
    Title.Text.Strings = (
      'Total Gain (dBi) - Top View')
    AxisBehind = False
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.Increment = 30.000000000000000000
    BottomAxis.LabelsFormat.Font.Name = 'Verdana'
    BottomAxis.MinimumRound = True
    BottomAxis.TicksInner.Color = 11119017
    BottomAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Axis.Color = 4210752
    DepthAxis.Grid.Color = 11119017
    DepthAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthAxis.TicksInner.Color = 11119017
    DepthAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Visible = True
    DepthTopAxis.Axis.Color = 4210752
    DepthTopAxis.Grid.Color = 11119017
    DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthTopAxis.TicksInner.Color = 11119017
    DepthTopAxis.Title.Font.Name = 'Verdana'
    DepthTopAxis.Visible = True
    LeftAxis.Axis.Color = 4210752
    LeftAxis.Grid.Color = 11119017
    LeftAxis.LabelsFormat.Font.Name = 'Verdana'
    LeftAxis.MaximumRound = True
    LeftAxis.MinimumRound = True
    LeftAxis.TicksInner.Color = 11119017
    LeftAxis.Title.Font.Name = 'Verdana'
    RightAxis.Axis.Color = 4210752
    RightAxis.Grid.Color = 11119017
    RightAxis.LabelsFormat.Font.Name = 'Verdana'
    RightAxis.MinimumRound = True
    RightAxis.TicksInner.Color = 11119017
    RightAxis.Title.Font.Name = 'Verdana'
    RightAxis.ZPosition = 0.010000000000000000
    TopAxis.Axis.Color = 4210752
    TopAxis.Grid.Color = 11119017
    TopAxis.LabelsFormat.Font.Name = 'Verdana'
    TopAxis.MinimumRound = True
    TopAxis.TicksInner.Color = 11119017
    TopAxis.Title.Font.Name = 'Verdana'
    TopAxis.ZPosition = 0.010000000000000000
    View3D = False
    Zoom.KeepAspectRatio = True
    TabOrder = 3
    DefaultCanvas = 'TGDIPlusCanvas'
    PrintMargins = (
      15
      12
      15
      12)
    ColorPaletteIndex = 13
    object PolarSeries2: TPolarSeries
      SeriesColor = 2474541
      Title = 'Total'
      XValues.Name = 'Angle'
      XValues.Order = loNone
      YValues.Name = 'Radius'
      YValues.Order = loNone
      Frame.InnerBrush.BackColor = clRed
      Frame.InnerBrush.Gradient.EndColor = clGray
      Frame.InnerBrush.Gradient.MidColor = clWhite
      Frame.InnerBrush.Gradient.StartColor = 4210752
      Frame.InnerBrush.Gradient.Visible = True
      Frame.MiddleBrush.BackColor = clYellow
      Frame.MiddleBrush.Gradient.EndColor = 8553090
      Frame.MiddleBrush.Gradient.MidColor = clWhite
      Frame.MiddleBrush.Gradient.StartColor = clGray
      Frame.MiddleBrush.Gradient.Visible = True
      Frame.OuterBrush.BackColor = clGreen
      Frame.OuterBrush.Gradient.EndColor = 4210752
      Frame.OuterBrush.Gradient.MidColor = clWhite
      Frame.OuterBrush.Gradient.StartColor = clSilver
      Frame.OuterBrush.Gradient.Visible = True
      Frame.Width = 4
      Shadow.Visible = False
      AngleIncrement = 30.000000000000000000
      AngleValues.Name = 'AngleValues'
      AngleValues.Order = loAscending
      AngleLabels.ClockWise = True
      CloseCircle = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      RotationAngle = 90
      Data = {
        01170000000000000000888A400000000000888A40CDCCCCCCCCCC7340000000
        000000504000000000000050406666666666E672400000000000407F40000000
        0000407F400000000000007240000000000020644000000000002064409A9999
        9999197140000000000078804000000000007880403333333333337040000000
        0000C062400000000000C062409A99999999996E400000000000988E40000000
        0000988E40CDCCCCCCCCCC6C4000000000007884400000000000788440000000
        0000006B40000000000068864000000000006886403333333333336940000000
        0000D08A400000000000D08A4066666666666667400000000000C06140000000
        0000C06140999999999999654000000000009887400000000000988740CDCCCC
        CCCCCC6340000000000028804000000000002880400000000000006240000000
        0000088740000000000008874033333333333360400000000000788840000000
        0000788840CCCCCCCCCCCC5C400000000000807B400000000000807B40343333
        3333335940000000000048834000000000004883409899999999995540000000
        0000F08C400000000000F08C4000000000000052400000000000C08840000000
        0000C08840C8CCCCCCCCCC4C400000000000008C400000000000008C40989999
        999999454000000000004075400000000000407540D0CCCCCCCCCC3C40000000
        0000F088400000000000F08840C0CCCCCCCCCC2C400000000000C88140000000
        0000C881400000000000000000}
      Detail = {0000000000}
    end
  end
  object Chart4: TChart
    Left = 173
    Top = 8
    Width = 428
    Height = 321
    BackWall.Brush.Gradient.Direction = gdBottomTop
    BackWall.Brush.Gradient.EndColor = clWhite
    BackWall.Brush.Gradient.StartColor = 15395562
    BackWall.Brush.Gradient.Visible = True
    BackWall.Transparent = False
    Foot.Font.Color = clBlue
    Foot.Font.Name = 'Verdana'
    Gradient.Direction = gdBottomTop
    Gradient.EndColor = clWhite
    Gradient.MidColor = 15395562
    Gradient.StartColor = 15395562
    Gradient.Visible = True
    LeftWall.Color = 14745599
    Legend.Font.Name = 'Verdana'
    Legend.FontSeriesColor = True
    Legend.LegendStyle = lsSeries
    Legend.Shadow.Transparency = 0
    RightWall.Color = 14745599
    Title.Font.Name = 'Verdana'
    Title.Text.Strings = (
      'Wire Segments')
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.LabelsFormat.Font.Name = 'Verdana'
    BottomAxis.TicksInner.Color = 11119017
    BottomAxis.Title.Caption = 'X'
    BottomAxis.Title.Font.Name = 'Verdana'
    BottomAxis.TitleSize = 10
    Chart3DPercent = 100
    DepthAxis.Axis.Color = 4210752
    DepthAxis.Grid.Color = 11119017
    DepthAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthAxis.LabelsSeparation = 0
    DepthAxis.TicksInner.Color = 11119017
    DepthAxis.Title.Caption = 'Y'
    DepthAxis.Title.Font.Name = 'Verdana'
    DepthAxis.TitleSize = 10
    DepthAxis.Visible = True
    DepthTopAxis.Axis.Color = 4210752
    DepthTopAxis.Grid.Color = 11119017
    DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthTopAxis.TicksInner.Color = 11119017
    DepthTopAxis.Title.Font.Name = 'Verdana'
    LeftAxis.Axis.Color = 4210752
    LeftAxis.Grid.Color = 11119017
    LeftAxis.LabelsFormat.Font.Name = 'Verdana'
    LeftAxis.TicksInner.Color = 11119017
    LeftAxis.Title.Caption = 'Z'
    LeftAxis.Title.Font.Name = 'Verdana'
    LeftAxis.TitleSize = 10
    RightAxis.Axis.Color = 4210752
    RightAxis.Grid.Color = 11119017
    RightAxis.LabelsFormat.Font.Name = 'Verdana'
    RightAxis.TicksInner.Color = 11119017
    RightAxis.Title.Font.Name = 'Verdana'
    RightAxis.Visible = False
    TopAxis.Axis.Color = 4210752
    TopAxis.Grid.Color = 11119017
    TopAxis.LabelsFormat.Font.Name = 'Verdana'
    TopAxis.TicksInner.Color = 11119017
    TopAxis.Title.Font.Name = 'Verdana'
    View3DOptions.Perspective = 18
    TabOrder = 4
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 0
    object Series2: TPoint3DSeries
      SeriesColor = clGreen
      Title = 'Design'
      LinePen.Visible = False
      Pointer.Depth = 3
      Pointer.HorizSize = 3
      Pointer.InflateMargins = True
      Pointer.Pen.Color = clDefault
      Pointer.Style = psRectangle
      Pointer.VertSize = 3
      XValues.Name = 'X'
      XValues.Order = loNone
      YValues.Name = 'Y'
      YValues.Order = loNone
      ZValues.Name = 'Z'
      ZValues.Order = loNone
    end
    object Series9: TPoint3DSeries
      Title = 'OptSWR'
      LinePen.Visible = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Pen.Color = clDefault
      Pointer.Style = psRectangle
      Pointer.Transparency = 48
      Pointer.VertSize = 2
      XValues.Name = 'X'
      XValues.Order = loNone
      YValues.Name = 'Y'
      YValues.Order = loNone
      ZValues.Name = 'Z'
      ZValues.Order = loNone
    end
    object Series10: TPoint3DSeries
      SeriesColor = 16711808
      Title = 'OptHorG'
      LinePen.Visible = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Pen.Color = clDefault
      Pointer.Style = psRectangle
      Pointer.Transparency = 48
      Pointer.VertSize = 2
      XValues.Name = 'X'
      XValues.Order = loNone
      YValues.Name = 'Y'
      YValues.Order = loNone
      ZValues.Name = 'Z'
      ZValues.Order = loNone
    end
  end
  object Chart5: TChart
    Left = 888
    Top = 214
    Width = 275
    Height = 200
    BackWall.Brush.Gradient.Direction = gdBottomTop
    BackWall.Brush.Gradient.EndColor = clWhite
    BackWall.Brush.Gradient.StartColor = 15395562
    BackWall.Brush.Gradient.Visible = True
    BackWall.Transparent = False
    Foot.Font.Color = clBlue
    Foot.Font.Name = 'Verdana'
    Gradient.Direction = gdBottomTop
    Gradient.EndColor = clWhite
    Gradient.MidColor = 15395562
    Gradient.StartColor = 15395562
    Gradient.Visible = True
    LeftWall.Color = 14745599
    Legend.Font.Name = 'Verdana'
    Legend.LegendStyle = lsSeries
    Legend.Shadow.Transparency = 0
    Legend.Visible = False
    RightWall.Color = 14745599
    Title.Font.Name = 'Verdana'
    Title.Text.Strings = (
      'Best Verticle Gain Slice (dBi) - Side View')
    AxisBehind = False
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.Increment = 30.000000000000000000
    BottomAxis.LabelsFormat.Font.Name = 'Verdana'
    BottomAxis.MinimumRound = True
    BottomAxis.TicksInner.Color = 11119017
    BottomAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Axis.Color = 4210752
    DepthAxis.Grid.Color = 11119017
    DepthAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthAxis.TicksInner.Color = 11119017
    DepthAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Visible = True
    DepthTopAxis.Axis.Color = 4210752
    DepthTopAxis.Grid.Color = 11119017
    DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthTopAxis.TicksInner.Color = 11119017
    DepthTopAxis.Title.Font.Name = 'Verdana'
    DepthTopAxis.Visible = True
    LeftAxis.Axis.Color = 4210752
    LeftAxis.Grid.Color = 11119017
    LeftAxis.LabelsFormat.Font.Name = 'Verdana'
    LeftAxis.MaximumRound = True
    LeftAxis.MinimumRound = True
    LeftAxis.TicksInner.Color = 11119017
    LeftAxis.Title.Font.Name = 'Verdana'
    RightAxis.Axis.Color = 4210752
    RightAxis.Grid.Color = 11119017
    RightAxis.LabelsFormat.Font.Name = 'Verdana'
    RightAxis.MinimumRound = True
    RightAxis.TicksInner.Color = 11119017
    RightAxis.Title.Font.Name = 'Verdana'
    RightAxis.ZPosition = 0.010000000000000000
    TopAxis.Axis.Color = 4210752
    TopAxis.Grid.Color = 11119017
    TopAxis.LabelsFormat.Font.Name = 'Verdana'
    TopAxis.MinimumRound = True
    TopAxis.TicksInner.Color = 11119017
    TopAxis.Title.Font.Name = 'Verdana'
    TopAxis.ZPosition = 0.010000000000000000
    View3D = False
    Zoom.KeepAspectRatio = True
    TabOrder = 5
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
    object PolarSeries3: TPolarSeries
      Title = 'Vertical'
      XValues.Name = 'Angle'
      XValues.Order = loNone
      YValues.Name = 'Radius'
      YValues.Order = loNone
      Frame.InnerBrush.BackColor = clRed
      Frame.InnerBrush.Gradient.EndColor = clGray
      Frame.InnerBrush.Gradient.MidColor = clWhite
      Frame.InnerBrush.Gradient.StartColor = 4210752
      Frame.InnerBrush.Gradient.Visible = True
      Frame.MiddleBrush.BackColor = clYellow
      Frame.MiddleBrush.Gradient.EndColor = 8553090
      Frame.MiddleBrush.Gradient.MidColor = clWhite
      Frame.MiddleBrush.Gradient.StartColor = clGray
      Frame.MiddleBrush.Gradient.Visible = True
      Frame.OuterBrush.BackColor = clGreen
      Frame.OuterBrush.Gradient.EndColor = 4210752
      Frame.OuterBrush.Gradient.MidColor = clWhite
      Frame.OuterBrush.Gradient.StartColor = clSilver
      Frame.OuterBrush.Gradient.Visible = True
      Frame.Width = 4
      Shadow.Visible = False
      AngleIncrement = 30.000000000000000000
      AngleValues.Name = 'AngleValues'
      AngleValues.Order = loAscending
      AngleLabels.ClockWise = True
      CloseCircle = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      RotationAngle = 90
      Data = {
        01170000000000000000888A400000000000888A40CDCCCCCCCCCC7340000000
        000000504000000000000050406666666666E672400000000000407F40000000
        0000407F400000000000007240000000000020644000000000002064409A9999
        9999197140000000000078804000000000007880403333333333337040000000
        0000C062400000000000C062409A99999999996E400000000000988E40000000
        0000988E40CDCCCCCCCCCC6C4000000000007884400000000000788440000000
        0000006B40000000000068864000000000006886403333333333336940000000
        0000D08A400000000000D08A4066666666666667400000000000C06140000000
        0000C06140999999999999654000000000009887400000000000988740CDCCCC
        CCCCCC6340000000000028804000000000002880400000000000006240000000
        0000088740000000000008874033333333333360400000000000788840000000
        0000788840CCCCCCCCCCCC5C400000000000807B400000000000807B40343333
        3333335940000000000048834000000000004883409899999999995540000000
        0000F08C400000000000F08C4000000000000052400000000000C08840000000
        0000C08840C8CCCCCCCCCC4C400000000000008C400000000000008C40989999
        999999454000000000004075400000000000407540D0CCCCCCCCCC3C40000000
        0000F088400000000000F08840C0CCCCCCCCCC2C400000000000C88140000000
        0000C881400000000000000000}
      Detail = {0000000000}
    end
  end
  object Chart6: TChart
    Left = 888
    Top = 419
    Width = 275
    Height = 200
    BackWall.Brush.Gradient.Direction = gdBottomTop
    BackWall.Brush.Gradient.EndColor = clWhite
    BackWall.Brush.Gradient.StartColor = 15395562
    BackWall.Brush.Gradient.Visible = True
    BackWall.Transparent = False
    Foot.Font.Color = clBlue
    Foot.Font.Name = 'Verdana'
    Gradient.Direction = gdBottomTop
    Gradient.EndColor = clWhite
    Gradient.MidColor = 15395562
    Gradient.StartColor = 15395562
    Gradient.Visible = True
    LeftWall.Color = 14745599
    Legend.Font.Name = 'Verdana'
    Legend.LegendStyle = lsSeries
    Legend.Shadow.Transparency = 0
    Legend.Visible = False
    RightWall.Color = 14745599
    Title.Font.Name = 'Verdana'
    Title.Text.Strings = (
      'Best Horizontal Gain Slice (dBi) - Side View')
    AxisBehind = False
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.Increment = 30.000000000000000000
    BottomAxis.LabelsFormat.Font.Name = 'Verdana'
    BottomAxis.MinimumRound = True
    BottomAxis.TicksInner.Color = 11119017
    BottomAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Axis.Color = 4210752
    DepthAxis.Grid.Color = 11119017
    DepthAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthAxis.TicksInner.Color = 11119017
    DepthAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Visible = True
    DepthTopAxis.Axis.Color = 4210752
    DepthTopAxis.Grid.Color = 11119017
    DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthTopAxis.TicksInner.Color = 11119017
    DepthTopAxis.Title.Font.Name = 'Verdana'
    DepthTopAxis.Visible = True
    LeftAxis.Axis.Color = 4210752
    LeftAxis.Grid.Color = 11119017
    LeftAxis.LabelsFormat.Font.Name = 'Verdana'
    LeftAxis.MaximumRound = True
    LeftAxis.MinimumRound = True
    LeftAxis.TicksInner.Color = 11119017
    LeftAxis.Title.Font.Name = 'Verdana'
    RightAxis.Axis.Color = 4210752
    RightAxis.Grid.Color = 11119017
    RightAxis.LabelsFormat.Font.Name = 'Verdana'
    RightAxis.MinimumRound = True
    RightAxis.TicksInner.Color = 11119017
    RightAxis.Title.Font.Name = 'Verdana'
    RightAxis.ZPosition = 0.010000000000000000
    TopAxis.Axis.Color = 4210752
    TopAxis.Grid.Color = 11119017
    TopAxis.LabelsFormat.Font.Name = 'Verdana'
    TopAxis.MinimumRound = True
    TopAxis.TicksInner.Color = 11119017
    TopAxis.Title.Font.Name = 'Verdana'
    TopAxis.ZPosition = 0.010000000000000000
    View3D = False
    Zoom.KeepAspectRatio = True
    TabOrder = 6
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
    object PolarSeries4: TPolarSeries
      SeriesColor = 9192
      Title = 'Horizontal'
      XValues.Name = 'Angle'
      XValues.Order = loNone
      YValues.Name = 'Radius'
      YValues.Order = loNone
      Frame.InnerBrush.BackColor = clRed
      Frame.InnerBrush.Gradient.EndColor = clGray
      Frame.InnerBrush.Gradient.MidColor = clWhite
      Frame.InnerBrush.Gradient.StartColor = 4210752
      Frame.InnerBrush.Gradient.Visible = True
      Frame.MiddleBrush.BackColor = clYellow
      Frame.MiddleBrush.Gradient.EndColor = 8553090
      Frame.MiddleBrush.Gradient.MidColor = clWhite
      Frame.MiddleBrush.Gradient.StartColor = clGray
      Frame.MiddleBrush.Gradient.Visible = True
      Frame.OuterBrush.BackColor = clGreen
      Frame.OuterBrush.Gradient.EndColor = 4210752
      Frame.OuterBrush.Gradient.MidColor = clWhite
      Frame.OuterBrush.Gradient.StartColor = clSilver
      Frame.OuterBrush.Gradient.Visible = True
      Frame.Width = 4
      Shadow.Visible = False
      AngleIncrement = 30.000000000000000000
      AngleValues.Name = 'AngleValues'
      AngleValues.Order = loAscending
      AngleLabels.ClockWise = True
      CloseCircle = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      RotationAngle = 90
      Data = {
        01170000000000000000888A400000000000888A40CDCCCCCCCCCC7340000000
        000000504000000000000050406666666666E672400000000000407F40000000
        0000407F400000000000007240000000000020644000000000002064409A9999
        9999197140000000000078804000000000007880403333333333337040000000
        0000C062400000000000C062409A99999999996E400000000000988E40000000
        0000988E40CDCCCCCCCCCC6C4000000000007884400000000000788440000000
        0000006B40000000000068864000000000006886403333333333336940000000
        0000D08A400000000000D08A4066666666666667400000000000C06140000000
        0000C06140999999999999654000000000009887400000000000988740CDCCCC
        CCCCCC6340000000000028804000000000002880400000000000006240000000
        0000088740000000000008874033333333333360400000000000788840000000
        0000788840CCCCCCCCCCCC5C400000000000807B400000000000807B40343333
        3333335940000000000048834000000000004883409899999999995540000000
        0000F08C400000000000F08C4000000000000052400000000000C08840000000
        0000C08840C8CCCCCCCCCC4C400000000000008C400000000000008C40989999
        999999454000000000004075400000000000407540D0CCCCCCCCCC3C40000000
        0000F088400000000000F08840C0CCCCCCCCCC2C400000000000C88140000000
        0000C881400000000000000000}
      Detail = {0000000000}
    end
  end
  object Make: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Make'
    TabOrder = 8
    OnClick = MakeClick
  end
  object Cancel: TButton
    Left = 92
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 10
    OnClick = CancelClick
  end
  object ResultTree: TTreeView
    Left = 173
    Top = 616
    Width = 428
    Height = 132
    Indent = 19
    ReadOnly = True
    TabOrder = 11
    Visible = False
    Items.NodeData = {
      03030000002E0000000000000000000000FFFFFFFFFFFFFFFF00000000000000
      00000000000108420065007300740020005300570052003A0000000000000000
      000000FFFFFFFFFFFFFFFF000000000000000000000000010E42006500730074
      00200048006F0072007A0020004700610069006E003A00000000000000000000
      00FFFFFFFFFFFFFFFF000000000000000000000000010E420065007300740020
      00560065007200740020004700610069006E00}
  end
  object Chart8: TChart
    Left = 173
    Top = 335
    Width = 428
    Height = 122
    BackWall.Brush.Gradient.Direction = gdBottomTop
    BackWall.Brush.Gradient.EndColor = clWhite
    BackWall.Brush.Gradient.StartColor = 15395562
    BackWall.Brush.Gradient.Visible = True
    BackWall.Transparent = False
    Foot.Font.Color = clBlue
    Foot.Font.Name = 'Verdana'
    Gradient.Direction = gdBottomTop
    Gradient.EndColor = clWhite
    Gradient.MidColor = 15395562
    Gradient.StartColor = 15395562
    Gradient.Visible = True
    LeftWall.Color = 14745599
    Legend.Font.Name = 'Verdana'
    Legend.LegendStyle = lsSeries
    Legend.Shadow.Transparency = 0
    RightWall.Color = 14745599
    Title.Font.Name = 'Verdana'
    Title.Text.Strings = (
      'Progress (SWR / Gain)')
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.LabelsFormat.Font.Name = 'Verdana'
    BottomAxis.TicksInner.Color = 11119017
    BottomAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Axis.Color = 4210752
    DepthAxis.Grid.Color = 11119017
    DepthAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthAxis.TicksInner.Color = 11119017
    DepthAxis.Title.Font.Name = 'Verdana'
    DepthTopAxis.Axis.Color = 4210752
    DepthTopAxis.Grid.Color = 11119017
    DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthTopAxis.TicksInner.Color = 11119017
    DepthTopAxis.Title.Font.Name = 'Verdana'
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Axis.Color = 4210752
    LeftAxis.AxisValuesFormat = '0.00E+0'
    LeftAxis.Grid.Color = 11119017
    LeftAxis.LabelsFormat.Font.Name = 'Verdana'
    LeftAxis.Logarithmic = True
    LeftAxis.Maximum = 100.000000000000000000
    LeftAxis.Minimum = 1.000000000000000000
    LeftAxis.RoundFirstLabel = False
    LeftAxis.TicksInner.Color = 11119017
    LeftAxis.Title.Caption = 'SWR'
    LeftAxis.Title.Font.Name = 'Verdana'
    RightAxis.Axis.Color = 4210752
    RightAxis.Grid.Color = 11119017
    RightAxis.LabelsFormat.Font.Name = 'Verdana'
    RightAxis.TicksInner.Color = 11119017
    RightAxis.Title.Caption = 'dB'
    RightAxis.Title.Font.Name = 'Verdana'
    TopAxis.Axis.Color = 4210752
    TopAxis.Grid.Color = 11119017
    TopAxis.LabelsFormat.Font.Name = 'Verdana'
    TopAxis.TicksInner.Color = 11119017
    TopAxis.Title.Font.Name = 'Verdana'
    View3D = False
    TabOrder = 12
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
    object Series5: TLineSeries
      SeriesColor = clGreen
      Title = 'VSWR'
      Brush.BackColor = clDefault
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = True
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series8: TLineSeries
      SeriesColor = clRed
      Title = 'Horz'
      VertAxis = aRightAxis
      Brush.BackColor = clDefault
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = True
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series11: TLineSeries
      SeriesColor = 12615680
      Title = 'Vert'
      VertAxis = aRightAxis
      Brush.BackColor = clDefault
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = True
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
  object Chart9: TChart
    Left = 173
    Top = 463
    Width = 428
    Height = 132
    BackWall.Brush.Gradient.Direction = gdBottomTop
    BackWall.Brush.Gradient.EndColor = clWhite
    BackWall.Brush.Gradient.StartColor = 15395562
    BackWall.Brush.Gradient.Visible = True
    BackWall.Transparent = False
    Foot.Font.Color = clBlue
    Foot.Font.Name = 'Verdana'
    Gradient.Direction = gdBottomTop
    Gradient.EndColor = clWhite
    Gradient.MidColor = 15395562
    Gradient.StartColor = 15395562
    Gradient.Visible = True
    LeftWall.Color = 14745599
    Legend.Font.Name = 'Verdana'
    Legend.Shadow.Transparency = 0
    RightWall.Color = 14745599
    Title.Font.Name = 'Verdana'
    Title.Text.Strings = (
      'Progress (Impedance)')
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.LabelsFormat.Font.Name = 'Verdana'
    BottomAxis.TicksInner.Color = 11119017
    BottomAxis.Title.Caption = 'Iteration'
    BottomAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Axis.Color = 4210752
    DepthAxis.Grid.Color = 11119017
    DepthAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthAxis.TicksInner.Color = 11119017
    DepthAxis.Title.Font.Name = 'Verdana'
    DepthTopAxis.Axis.Color = 4210752
    DepthTopAxis.Grid.Color = 11119017
    DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthTopAxis.TicksInner.Color = 11119017
    DepthTopAxis.Title.Font.Name = 'Verdana'
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Axis.Color = 4210752
    LeftAxis.Grid.Color = 11119017
    LeftAxis.LabelsFormat.Font.Name = 'Verdana'
    LeftAxis.Maximum = 100.000000000000000000
    LeftAxis.TicksInner.Color = 11119017
    LeftAxis.Title.Caption = 'R'
    LeftAxis.Title.Font.Name = 'Verdana'
    RightAxis.Automatic = False
    RightAxis.AutomaticMaximum = False
    RightAxis.AutomaticMinimum = False
    RightAxis.Axis.Color = 4210752
    RightAxis.Grid.Color = 11119017
    RightAxis.LabelsFormat.Font.Name = 'Verdana'
    RightAxis.Maximum = 300.000000000000000000
    RightAxis.Minimum = -300.000000000000000000
    RightAxis.TicksInner.Color = 11119017
    RightAxis.Title.Caption = 'X'
    RightAxis.Title.Font.Name = 'Verdana'
    TopAxis.Axis.Color = 4210752
    TopAxis.Grid.Color = 11119017
    TopAxis.LabelsFormat.Font.Name = 'Verdana'
    TopAxis.TicksInner.Color = 11119017
    TopAxis.Title.Font.Name = 'Verdana'
    View3D = False
    TabOrder = 13
    DefaultCanvas = 'TGDIPlusCanvas'
    PrintMargins = (
      15
      36
      15
      36)
    ColorPaletteIndex = 13
    object Series6: TLineSeries
      Title = 'R'
      Brush.BackColor = clDefault
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = True
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series7: TLineSeries
      Title = 'X'
      VertAxis = aRightAxis
      Brush.BackColor = clDefault
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = True
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
  object ErrorMemo: TMemo
    Left = 888
    Top = 8
    Width = 275
    Height = 200
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 9
  end
  object Chart7: TChart
    Left = 173
    Top = 601
    Width = 428
    Height = 138
    BackWall.Brush.Gradient.Direction = gdBottomTop
    BackWall.Brush.Gradient.EndColor = clWhite
    BackWall.Brush.Gradient.StartColor = 15395562
    BackWall.Brush.Gradient.Visible = True
    BackWall.Transparent = False
    Foot.Font.Color = clBlue
    Foot.Font.Name = 'Verdana'
    Gradient.Direction = gdBottomTop
    Gradient.EndColor = clWhite
    Gradient.MidColor = 15395562
    Gradient.StartColor = 15395562
    Gradient.Visible = True
    LeftWall.Color = 14745599
    Legend.Font.Name = 'Verdana'
    Legend.LegendStyle = lsSeries
    Legend.Shadow.Transparency = 0
    RightWall.Color = 14745599
    Title.Font.Name = 'Verdana'
    Title.Text.Strings = (
      'Frequency Sweep')
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.LabelsFormat.Font.Name = 'Verdana'
    BottomAxis.TicksInner.Color = 11119017
    BottomAxis.Title.Caption = 'Frequency (MHz)'
    BottomAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Axis.Color = 4210752
    DepthAxis.Grid.Color = 11119017
    DepthAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthAxis.TicksInner.Color = 11119017
    DepthAxis.Title.Font.Name = 'Verdana'
    DepthTopAxis.Axis.Color = 4210752
    DepthTopAxis.Grid.Color = 11119017
    DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
    DepthTopAxis.TicksInner.Color = 11119017
    DepthTopAxis.Title.Font.Name = 'Verdana'
    LeftAxis.Axis.Color = 4210752
    LeftAxis.Grid.Color = 11119017
    LeftAxis.LabelsFormat.Font.Name = 'Verdana'
    LeftAxis.TicksInner.Color = 11119017
    LeftAxis.Title.Caption = 'VSWR'
    LeftAxis.Title.Font.Name = 'Verdana'
    RightAxis.Axis.Color = 4210752
    RightAxis.Grid.Color = 11119017
    RightAxis.LabelsFormat.Font.Name = 'Verdana'
    RightAxis.TicksInner.Color = 11119017
    RightAxis.Title.Caption = 'Total Gain (dBi)'
    RightAxis.Title.Font.Name = 'Verdana'
    TopAxis.Axis.Color = 4210752
    TopAxis.Grid.Color = 11119017
    TopAxis.LabelsFormat.Font.Name = 'Verdana'
    TopAxis.TicksInner.Color = 11119017
    TopAxis.Title.Font.Name = 'Verdana'
    View3D = False
    TabOrder = 7
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
    object Series3: TLineSeries
      Title = 'VSWR'
      Brush.BackColor = clDefault
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = True
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series4: TLineSeries
      Title = 'Gain'
      VertAxis = aRightAxis
      Brush.BackColor = clDefault
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = True
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
  object ProgressBar1: TProgressBar
    Left = 608
    Top = 624
    Width = 555
    Height = 17
    Step = 1
    TabOrder = 14
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '*.nec'
    Filter = 'NEC Files|*.nec|All Files|*.*'
    Left = 192
    Top = 8
  end
  object Timer1: TTimer
    Interval = 50
    OnTimer = Timer1Timer
    Left = 256
    Top = 8
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '.tmp'
    Filter = 'NEC Input Files|*.nec|All Files|*.*'
    Left = 624
    Top = 624
  end
end
