Attribute VB_Name = "StageMaxCsv"
Option Explicit
Sub StageMaxCsvOut()

    Dim csvFilePath As String
    Dim iCount As Long
    Dim jCount As Long
    Dim kCount As Long
    Dim maxRow As Long
    Dim maxCol As Long
    Dim fileNo As Integer
    Dim FileName As String
          
    Dim 行最大 As Integer
    
    Dim 列最大 As Integer
    
    Dim 最大数() As Integer
    
    Dim Tmp As Integer
    
    Tmp = 0
    
    ' 最終行
    maxRow = ActiveSheet.Range("A1").End(xlDown).Row
    ' 最終列
    maxCol = ActiveSheet.Range("A1").End(xlToRight).Column
    
    ReDim 最大数(maxCol)
    
    For iCount = 1 To maxCol
        Tmp = 0
        For jCount = 2 To maxRow
            If Cells(jCount, iCount).Value <> 0 Then
                Tmp = Tmp + 1
            End If
        Next jCount
            最大数(iCount) = Tmp
    Next iCount
     
    ' ファイル名の取得（拡張子を除く）
    FileName = Left(ActiveWorkbook.Name, InStrRev(ActiveWorkbook.Name, ".", -1, vbTextCompare) - 1)
    ' CSVファイルパスの作成
    csvFilePath = ActiveWorkbook.Path & "\" & FileName & "Max.csv"
   
    ' ファイル番号
    fileNo = FreeFile
    ' ファイル開く
    Open csvFilePath For Output As #fileNo
            
    ' 縦方向ループ（最終行まで）
    For iCount = 1 To maxCol
        ' ファイル出力（改行なし）
        Print #fileNo, 最大数(iCount) & ",";
    Next iCount

    ' ファイルを閉じる
    Close #fileNo
End Sub

