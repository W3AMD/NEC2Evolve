object Form1: TForm1
  Left = 411
  Top = 338
  Caption = 'NECEvolve Alpha Development Version 0.1'
  ClientHeight = 793
  ClientWidth = 1227
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object StatusCaption: TLabel
    Left = 11
    Top = 741
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
    Top = 464
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
    Top = 512
    Width = 78
    Height = 13
    Caption = 'Disable Vec Cnt:'
  end
  object EnableCount: TLabel
    Left = 96
    Top = 488
    Width = 6
    Height = 13
    Caption = '0'
  end
  object DisableCount: TLabel
    Left = 96
    Top = 512
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label21: TLabel
    Left = 8
    Top = 536
    Width = 60
    Height = 13
    Caption = 'Total Count:'
  end
  object TotalCount: TLabel
    Left = 80
    Top = 536
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label22: TLabel
    Left = 8
    Top = 560
    Width = 62
    Height = 13
    Caption = 'SWR Target:'
  end
  object Label23: TLabel
    Left = 8
    Top = 584
    Width = 85
    Height = 13
    Caption = 'Horz Gain Target:'
  end
  object SWRTarget: TLabel
    Left = 80
    Top = 560
    Width = 6
    Height = 13
    Caption = '0'
  end
  object HorzGainTarget: TLabel
    Left = 104
    Top = 584
    Width = 6
    Height = 13
    Caption = '0'
  end
  object OptimizationMode: TLabel
    Left = 8
    Top = 608
    Width = 25
    Height = 13
    Caption = 'None'
  end
  object Label24: TLabel
    Left = 8
    Top = 632
    Width = 72
    Height = 13
    Caption = 'Enabled Wires:'
  end
  object Label25: TLabel
    Left = 8
    Top = 656
    Width = 74
    Height = 13
    Caption = 'Disabled Wires:'
  end
  object EnabledCount: TLabel
    Left = 88
    Top = 632
    Width = 6
    Height = 13
    Caption = '0'
  end
  object DisabledCount: TLabel
    Left = 88
    Top = 656
    Width = 6
    Height = 13
    Caption = '0'
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
    Left = 525
    Top = 269
    Width = 346
    Height = 255
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
    RightWall.Color = 14745599
    Title.Font.Name = 'Verdana'
    Title.Text.Strings = (
      'Verticle Gain (dBi) - Top View')
    AxisBehind = False
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.Increment = 15.000000000000000000
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
      AngleIncrement = 15.000000000000000000
      AngleValues.Name = 'AngleValues'
      AngleValues.Order = loAscending
      CloseCircle = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      Data = {
        01170000000000000000888A400000000000888A409A99999999994540000000
        00000050400000000000005040CDCCCCCCCCCC4C400000000000407F40000000
        0000407F400000000000005240000000000020644000000000002064409A9999
        9999995540000000000078804000000000007880403333333333335940000000
        0000C062400000000000C06240CDCCCCCCCCCC5C400000000000988E40000000
        0000988E40333333333333604000000000007884400000000000788440000000
        000000624000000000006886400000000000688640CDCCCCCCCCCC6340000000
        0000D08A400000000000D08A409A999999999965400000000000C06140000000
        0000C06140676666666666674000000000009887400000000000988740333333
        3333336940000000000028804000000000002880400000000000006B40000000
        00000887400000000000088740CDCCCCCCCCCC6C400000000000788840000000
        00007888409A99999999996E400000000000807B400000000000807B40333333
        3333337040000000000048834000000000004883409A99999999197140000000
        0000F08C400000000000F08C4000000000000072400000000000C08840000000
        0000C088406766666666E672400000000000008C400000000000008C40CDCCCC
        CCCCCC7340000000000040754000000000004075403333333333B37440000000
        0000F088400000000000F088409A999999999975400000000000C88140000000
        0000C881400000000000807640}
      Detail = {0000000000}
    end
  end
  object Chart2: TChart
    Left = 173
    Top = 269
    Width = 346
    Height = 255
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
    RightWall.Color = 14745599
    Title.Font.Name = 'Verdana'
    Title.Text.Strings = (
      'Horizontal Gain (dBi) - Top View')
    AxisBehind = False
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.Increment = 15.000000000000000000
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
      AngleIncrement = 15.000000000000000000
      AngleValues.Name = 'AngleValues'
      AngleValues.Order = loAscending
      CloseCircle = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      Data = {
        01170000000000000000888A400000000000888A409A99999999994540000000
        00000050400000000000005040CDCCCCCCCCCC4C400000000000407F40000000
        0000407F400000000000005240000000000020644000000000002064409A9999
        9999995540000000000078804000000000007880403333333333335940000000
        0000C062400000000000C06240CDCCCCCCCCCC5C400000000000988E40000000
        0000988E40333333333333604000000000007884400000000000788440000000
        000000624000000000006886400000000000688640CDCCCCCCCCCC6340000000
        0000D08A400000000000D08A409A999999999965400000000000C06140000000
        0000C06140676666666666674000000000009887400000000000988740333333
        3333336940000000000028804000000000002880400000000000006B40000000
        00000887400000000000088740CDCCCCCCCCCC6C400000000000788840000000
        00007888409A99999999996E400000000000807B400000000000807B40333333
        3333337040000000000048834000000000004883409A99999999197140000000
        0000F08C400000000000F08C4000000000000072400000000000C08840000000
        0000C088406766666666E672400000000000008C400000000000008C40CDCCCC
        CCCCCC7340000000000040754000000000004075403333333333B37440000000
        0000F088400000000000F088409A999999999975400000000000C88140000000
        0000C881400000000000807640}
      Detail = {0000000000}
    end
  end
  object Chart3: TChart
    Left = 525
    Top = 8
    Width = 346
    Height = 255
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
    RightWall.Color = 14745599
    Title.Font.Name = 'Verdana'
    Title.Text.Strings = (
      'Total Gain (dBi) - Top View')
    AxisBehind = False
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.Increment = 15.000000000000000000
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
      AngleIncrement = 15.000000000000000000
      AngleValues.Name = 'AngleValues'
      AngleValues.Order = loAscending
      CloseCircle = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      Data = {
        01170000000000000000888A400000000000888A409A99999999994540000000
        00000050400000000000005040CDCCCCCCCCCC4C400000000000407F40000000
        0000407F400000000000005240000000000020644000000000002064409A9999
        9999995540000000000078804000000000007880403333333333335940000000
        0000C062400000000000C06240CDCCCCCCCCCC5C400000000000988E40000000
        0000988E40333333333333604000000000007884400000000000788440000000
        000000624000000000006886400000000000688640CDCCCCCCCCCC6340000000
        0000D08A400000000000D08A409A999999999965400000000000C06140000000
        0000C06140676666666666674000000000009887400000000000988740333333
        3333336940000000000028804000000000002880400000000000006B40000000
        00000887400000000000088740CDCCCCCCCCCC6C400000000000788840000000
        00007888409A99999999996E400000000000807B400000000000807B40333333
        3333337040000000000048834000000000004883409A99999999197140000000
        0000F08C400000000000F08C4000000000000072400000000000C08840000000
        0000C088406766666666E672400000000000008C400000000000008C40CDCCCC
        CCCCCC7340000000000040754000000000004075403333333333B37440000000
        0000F088400000000000F088409A999999999975400000000000C88140000000
        0000C881400000000000807640}
      Detail = {0000000000}
    end
  end
  object Chart4: TChart
    Left = 173
    Top = 8
    Width = 346
    Height = 255
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
    BottomAxis.Title.Font.Name = 'Verdana'
    Chart3DPercent = 100
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
    LeftAxis.Axis.Color = 4210752
    LeftAxis.Grid.Color = 11119017
    LeftAxis.LabelsFormat.Font.Name = 'Verdana'
    LeftAxis.TicksInner.Color = 11119017
    LeftAxis.Title.Font.Name = 'Verdana'
    RightAxis.Axis.Color = 4210752
    RightAxis.Grid.Color = 11119017
    RightAxis.LabelsFormat.Font.Name = 'Verdana'
    RightAxis.TicksInner.Color = 11119017
    RightAxis.Title.Font.Name = 'Verdana'
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
    Left = 877
    Top = 269
    Width = 346
    Height = 255
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
      'Best Verticle Gain Slice (dBi) - Side View')
    AxisBehind = False
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.Increment = 15.000000000000000000
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
      AngleIncrement = 15.000000000000000000
      AngleValues.Name = 'AngleValues'
      AngleValues.Order = loAscending
      CloseCircle = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      Data = {
        01170000000000000000888A400000000000888A409A99999999994540000000
        00000050400000000000005040CDCCCCCCCCCC4C400000000000407F40000000
        0000407F400000000000005240000000000020644000000000002064409A9999
        9999995540000000000078804000000000007880403333333333335940000000
        0000C062400000000000C06240CDCCCCCCCCCC5C400000000000988E40000000
        0000988E40333333333333604000000000007884400000000000788440000000
        000000624000000000006886400000000000688640CDCCCCCCCCCC6340000000
        0000D08A400000000000D08A409A999999999965400000000000C06140000000
        0000C06140676666666666674000000000009887400000000000988740333333
        3333336940000000000028804000000000002880400000000000006B40000000
        00000887400000000000088740CDCCCCCCCCCC6C400000000000788840000000
        00007888409A99999999996E400000000000807B400000000000807B40333333
        3333337040000000000048834000000000004883409A99999999197140000000
        0000F08C400000000000F08C4000000000000072400000000000C08840000000
        0000C088406766666666E672400000000000008C400000000000008C40CDCCCC
        CCCCCC7340000000000040754000000000004075403333333333B37440000000
        0000F088400000000000F088409A999999999975400000000000C88140000000
        0000C881400000000000807640}
      Detail = {0000000000}
    end
  end
  object Chart6: TChart
    Left = 173
    Top = 530
    Width = 346
    Height = 258
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
      'Best Horizontal Gain Slice (dBi) - Side View')
    AxisBehind = False
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.Increment = 15.000000000000000000
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
      AngleIncrement = 15.000000000000000000
      AngleValues.Name = 'AngleValues'
      AngleValues.Order = loAscending
      CloseCircle = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      Data = {
        01170000000000000000888A400000000000888A409A99999999994540000000
        00000050400000000000005040CDCCCCCCCCCC4C400000000000407F40000000
        0000407F400000000000005240000000000020644000000000002064409A9999
        9999995540000000000078804000000000007880403333333333335940000000
        0000C062400000000000C06240CDCCCCCCCCCC5C400000000000988E40000000
        0000988E40333333333333604000000000007884400000000000788440000000
        000000624000000000006886400000000000688640CDCCCCCCCCCC6340000000
        0000D08A400000000000D08A409A999999999965400000000000C06140000000
        0000C06140676666666666674000000000009887400000000000988740333333
        3333336940000000000028804000000000002880400000000000006B40000000
        00000887400000000000088740CDCCCCCCCCCC6C400000000000788840000000
        00007888409A99999999996E400000000000807B400000000000807B40333333
        3333337040000000000048834000000000004883409A99999999197140000000
        0000F08C400000000000F08C4000000000000072400000000000C08840000000
        0000C088406766666666E672400000000000008C400000000000008C40CDCCCC
        CCCCCC7340000000000040754000000000004075403333333333B37440000000
        0000F088400000000000F088409A999999999975400000000000C88140000000
        0000C881400000000000807640}
      Detail = {0000000000}
    end
  end
  object Chart7: TChart
    Left = 877
    Top = 8
    Width = 346
    Height = 255
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
  object Make: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Make'
    TabOrder = 8
    OnClick = MakeClick
  end
  object ErrorMemo: TMemo
    Left = 877
    Top = 530
    Width = 346
    Height = 122
    ReadOnly = True
    TabOrder = 9
  end
  object Cancel: TButton
    Left = 17
    Top = 760
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 10
    OnClick = CancelClick
  end
  object ResultTree: TTreeView
    Left = 877
    Top = 656
    Width = 346
    Height = 132
    Indent = 19
    ReadOnly = True
    TabOrder = 11
    Items.NodeData = {
      03030000002E0000000000000000000000FFFFFFFFFFFFFFFF00000000000000
      00000000000108420065007300740020005300570052003A0000000000000000
      000000FFFFFFFFFFFFFFFF000000000000000000000000010E42006500730074
      00200048006F0072007A0020004700610069006E003A00000000000000000000
      00FFFFFFFFFFFFFFFF000000000000000000000000010E420065007300740020
      00560065007200740020004700610069006E00}
  end
  object Chart8: TChart
    Left = 525
    Top = 530
    Width = 346
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
      'SWR Progress')
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
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Axis.Color = 4210752
    LeftAxis.AxisValuesFormat = '0.00E+0'
    LeftAxis.Grid.Color = 11119017
    LeftAxis.LabelsFormat.Font.Name = 'Verdana'
    LeftAxis.Logarithmic = True
    LeftAxis.Minimum = 1.000000000000000000
    LeftAxis.RoundFirstLabel = False
    LeftAxis.TicksInner.Color = 11119017
    LeftAxis.Title.Font.Name = 'Verdana'
    RightAxis.Axis.Color = 4210752
    RightAxis.Grid.Color = 11119017
    RightAxis.LabelsFormat.Font.Name = 'Verdana'
    RightAxis.TicksInner.Color = 11119017
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
      Title = 'HorzGain'
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
    Left = 525
    Top = 656
    Width = 346
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
      'Impedance')
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
    LeftAxis.Axis.Color = 4210752
    LeftAxis.Grid.Color = 11119017
    LeftAxis.LabelsFormat.Font.Name = 'Verdana'
    LeftAxis.TicksInner.Color = 11119017
    LeftAxis.Title.Font.Name = 'Verdana'
    RightAxis.Axis.Color = 4210752
    RightAxis.Grid.Color = 11119017
    RightAxis.LabelsFormat.Font.Name = 'Verdana'
    RightAxis.TicksInner.Color = 11119017
    RightAxis.Title.Font.Name = 'Verdana'
    TopAxis.Axis.Color = 4210752
    TopAxis.Grid.Color = 11119017
    TopAxis.LabelsFormat.Font.Name = 'Verdana'
    TopAxis.TicksInner.Color = 11119017
    TopAxis.Title.Font.Name = 'Verdana'
    View3D = False
    TabOrder = 13
    DefaultCanvas = 'TGDIPlusCanvas'
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
  object OpenDialog1: TOpenDialog
    DefaultExt = '*.nec'
    Filter = '*.nec|*.nec'
    Left = 192
    Top = 8
  end
  object Timer1: TTimer
    Interval = 50
    OnTimer = Timer1Timer
    Left = 256
    Top = 8
  end
end
