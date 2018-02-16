Attribute VB_Name = "CsvOut"
Option Explicit
Sub CSV�o��()
Attribute CSV�o��.VB_Description = "�t�@�C����CSV�o��"
Attribute CSV�o��.VB_ProcData.VB_Invoke_Func = "s\n14"
    Dim csvFilePath As String
    Dim iCount As Long
    Dim jCount As Long
    Dim kCount As Long
    Dim maxRow As Long
    Dim maxCol As Long
    Dim fileNo As Integer
    Dim FileName As String
    
    ' �t�@�C�����̎擾�i�g���q�������j
    FileName = Left(ActiveWorkbook.Name, InStrRev(ActiveWorkbook.Name, ".", -1, vbTextCompare) - 1)
    ' CSV�t�@�C���p�X�̍쐬
    csvFilePath = ActiveWorkbook.Path & "\" & FileName & ".csv"
    ' �ŏI�s
    maxRow = ActiveSheet.Range("A1").End(xlDown).Row
    ' �ŏI��
    maxCol = ActiveSheet.Range("A1").End(xlToRight).Column
    ' �t�@�C���ԍ�
    fileNo = FreeFile

    ' �t�@�C���J��
    Open csvFilePath For Output As #fileNo

    ' �c�������[�v�i�ŏI�s�܂Łj
    For iCount = 1 To maxRow
        ' ���������[�v�i�ŏI��|�P�܂Łj
        For jCount = 1 To maxCol - 1
            ' �t�@�C���o�́i���s�Ȃ��j
            Print #fileNo, Cells(iCount, jCount) & ",";

            ' ���[�v�J�E���^���R�s�[
            kCount = jCount
        Next jCount
        ' �ŏI����t�@�C���o�́i���s�t���j
        Print #fileNo, Cells(iCount, kCount + 1) & ","
    Next iCount

    ' �t�@�C�������
    Close #fileNo
'
    ActiveWorkbook.Save
End Sub
