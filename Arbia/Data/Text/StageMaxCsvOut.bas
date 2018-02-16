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
          
    Dim �s�ő� As Integer
    
    Dim ��ő� As Integer
    
    Dim �ő吔() As Integer
    
    Dim Tmp As Integer
    
    Tmp = 0
    
    ' �ŏI�s
    maxRow = ActiveSheet.Range("A1").End(xlDown).Row
    ' �ŏI��
    maxCol = ActiveSheet.Range("A1").End(xlToRight).Column
    
    ReDim �ő吔(maxCol)
    
    For iCount = 1 To maxCol
        Tmp = 0
        For jCount = 2 To maxRow
            If Cells(jCount, iCount).Value <> 0 Then
                Tmp = Tmp + 1
            End If
        Next jCount
            �ő吔(iCount) = Tmp
    Next iCount
     
    ' �t�@�C�����̎擾�i�g���q�������j
    FileName = Left(ActiveWorkbook.Name, InStrRev(ActiveWorkbook.Name, ".", -1, vbTextCompare) - 1)
    ' CSV�t�@�C���p�X�̍쐬
    csvFilePath = ActiveWorkbook.Path & "\" & FileName & "Max.csv"
   
    ' �t�@�C���ԍ�
    fileNo = FreeFile
    ' �t�@�C���J��
    Open csvFilePath For Output As #fileNo
            
    ' �c�������[�v�i�ŏI�s�܂Łj
    For iCount = 1 To maxCol
        ' �t�@�C���o�́i���s�Ȃ��j
        Print #fileNo, �ő吔(iCount) & ",";
    Next iCount

    ' �t�@�C�������
    Close #fileNo
End Sub

