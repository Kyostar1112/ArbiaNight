Attribute VB_Name = "ArbiaStageCheck"
Option Explicit
' Public �͕W�����W���[���ł̂ݒ�`�ł���
 Public Type StageFlg
    ��      As Boolean
    ��      As Boolean
    �G      As Integer
    �ۏ�    As Integer
    �l�p��  As Boolean
    �h�A    As Boolean
    �y���f������ As Integer
    ����    As Boolean
    ����    As Boolean
    ���Ƃ��� As Integer
    �S�[��  As Boolean
 End Type
Sub �G���A�`�F�b�N()
Attribute �G���A�`�F�b�N.VB_ProcData.VB_Invoke_Func = "n\n14"

    ' Macro1 Macro
    Const �ۏ��̈ړ��͈� As Integer = 15
    Const �ۏ��̏o��ʒu As Integer = 4
    
    Const �G�̍s���͈� As Integer = 13
    Const �G�̏o��ʒu As Integer = 6
    
    Const ���Ƃ����傫�� As Integer = 12
    Const �����f���}�b�N�X As Integer = 4
    Const �ǃ��f���}�b�N�X As Integer = 1
    Dim ���Ԃ�h�~ As StageFlg
      
    Dim �s�ő� As Integer
    
    Dim ��ő� As Integer

    �s�ő� = Cells(Rows.Count, 1).End(xlUp).Row
    
    ��ő� = Range("a1").End(xlToRight).Column
    
   ' MsgBox "�w�肳�ꂽ��̈�ԉ��[�̃Z����" & r & "�s�ڂł��B"
     '�w�i�F������
    Worksheets("StageData").Cells.Interior.ColorIndex = xlNone
    
    Range("A1:L10").Cells.Interior.ColorIndex = 16
            
   
    'For���J�n
     Dim i As Long
        For i = 11 To �s�ő�
        Dim j As Long
        For j = 1 To ��ő�
            '�֐��`�F�b�N�p
            'If Not Cells(i, j).HasFormula Then
            If Cells(i, j) = "" Then
             '��
              Cells(i, j) = 0
            End If
        Next j
            
           '�G�̍s���͈͂�
           If Cells(i + �G�̏o��ʒu, 3).Value <> 0 Then
                If ���Ԃ�h�~.�G = 0 Then
                    ���Ԃ�h�~.�G = �G�̍s���͈�
                    Else
                    MsgBox ("�G�̍s���͈͂ǂ������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
                End If
           End If
          
          '�ۏ��̈ړ��͈͂�
           If Cells(i + 4, 4).Value <> 0 Then
                If ���Ԃ�h�~.�ۏ� = 0 Then
                    ���Ԃ�h�~.�ۏ� = �ۏ��̈ړ��͈�
                    Else
                    'MsgBox ("�ۏ��̈ړ��͈͂ǂ������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
                    ���Ԃ�h�~.�ۏ� = �ۏ��̈ړ��͈�
               End If
           End If
           
           '�l�p����
           If Cells(i, 5).Value > 0 Then
              ���Ԃ�h�~.�l�p�� = True
              Else
              ���Ԃ�h�~.�l�p�� = False
           End If
           
           '�h�A��
           If Cells(i, 6).Value > 0 Then
              ���Ԃ�h�~.�h�A = True
              Else
              ���Ԃ�h�~.�h�A = False
           End If
           
            '�y���f��������
           If Cells(i, 7).Value > 0 Then
              ���Ԃ�h�~.�y���f������ = Cells(i, 7).Value
              Else
              ���Ԃ�h�~.�y���f������ = 0
           End If
           
            '������
           If Cells(i, 8).Value > 0 Then
              ���Ԃ�h�~.���� = True
              Else
              ���Ԃ�h�~.���� = False
           End If
           
           '���ǂ�
           If Cells(i, 9).Value > 0 Then
              ���Ԃ�h�~.���� = True
              Else
              ���Ԃ�h�~.���� = False
           End If
           
           '���Ƃ����͈̔͂�
           If Cells(i, 10).Value > 0 Then
                If ���Ԃ�h�~.���Ƃ��� <= 0 Then
                ���Ԃ�h�~.���Ƃ��� = ���Ƃ����傫��
                Else
                MsgBox ("���Ƃ����ǂ��������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
                End If
           End If
          
          '�S�[����
           If Cells(i, 11).Value > 0 Then
              ���Ԃ�h�~.�S�[�� = True
              Else
              ���Ԃ�h�~.�S�[�� = False
           End If
           
           
'���Ԃ肩�ǂ����m�F�͂�����
          If ���Ԃ�h�~.�G > 0 Then
            If ���Ԃ�h�~.�ۏ� > 0 Then
                MsgBox ("�G�Ɗۏ������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.�l�p�� = True Then
                MsgBox ("�G�Ǝl�p�������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.�h�A = True Then
                MsgBox ("�G�ƃh�A�����Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.�y���f������ = True Then
                MsgBox ("�G�ƃy���f�����������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.���� = True Then
                MsgBox ("�G�Ƒ��������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.���� = True Then
                MsgBox ("�G�Ƒ��ǂ����Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.���Ƃ��� > 0 Then
                MsgBox ("�G�Ɨ��Ƃ��������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.�S�[�� = True Then
                MsgBox ("�G�ƃS�[�������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
          End If
          If ���Ԃ�h�~.�ۏ� > 0 Then
            If ���Ԃ�h�~.�l�p�� = True Then
                MsgBox ("�ۏ��Ǝl�p�������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.�h�A = True Then
                MsgBox ("�ۏ��ƃh�A�����Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.�y���f������ = True Then
                MsgBox ("�ۏ��ƃy���f�����������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.���� = True Then
                MsgBox ("�ۏ��Ƒ��������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.���� = True Then
                MsgBox ("�ۏ��Ƒ��ǂ����Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.���Ƃ��� > 0 Then
                MsgBox ("�ۏ��Ɨ��Ƃ��������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.�S�[�� = True Then
                MsgBox ("�ۏ��ƃS�[�������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
          End If
          If ���Ԃ�h�~.�l�p�� > 0 Then
            If ���Ԃ�h�~.�h�A = True Then
                MsgBox ("�l�p���ƃh�A�����Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.�y���f������ = True Then
                MsgBox ("�l�p���ƃy���f�����������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.���� = True Then
                MsgBox ("�l�p���Ƒ��������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.���� = True Then
                MsgBox ("�l�p���Ƒ��ǂ����Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.���Ƃ��� > 0 Then
                MsgBox ("�l�p���Ɨ��Ƃ��������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
            If ���Ԃ�h�~.�S�[�� = True Then
                MsgBox ("�l�p���ƃS�[�������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
            End If
          End If
         If ���Ԃ�h�~.�h�A = True Then
           If ���Ԃ�h�~.�y���f������ = True Then
               MsgBox ("�h�A�ƃy���f�����������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
           If ���Ԃ�h�~.���� = True Then
               MsgBox ("�h�A�Ƒ��������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
           If ���Ԃ�h�~.���� = True Then
               MsgBox ("�h�A�Ƒ��ǂ����Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
           If ���Ԃ�h�~.���Ƃ��� > 0 Then
               MsgBox ("�h�A�Ɨ��Ƃ��������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
           If ���Ԃ�h�~.�S�[�� = True Then
               MsgBox ("�h�A�ƃS�[�������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
         End If
          
         If ���Ԃ�h�~.�y���f������ = True Then
           If ���Ԃ�h�~.���� = True Then
               MsgBox ("�y���f�������Ƒ��������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
           If ���Ԃ�h�~.���� = True Then
               MsgBox ("�y���f�������Ƒ��ǂ����Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
           If ���Ԃ�h�~.���Ƃ��� > 0 Then
               MsgBox ("�y���f�������Ɨ��Ƃ��������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
           If ���Ԃ�h�~.�S�[�� = True Then
               MsgBox ("�y���f�������ƃS�[�������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
         End If
        
        If ���Ԃ�h�~.���� = True Then
           If ���Ԃ�h�~.���� = True Then
               MsgBox ("�����Ƒ��ǂ����Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
           If ���Ԃ�h�~.���Ƃ��� > 0 Then
               MsgBox ("�����Ɨ��Ƃ��������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
           If ���Ԃ�h�~.�S�[�� = True Then
               MsgBox ("�����ƃS�[�������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
         End If
      
        If ���Ԃ�h�~.���� = True Then
            If ���Ԃ�h�~.���Ƃ��� > 0 Then
               MsgBox ("���ǂƗ��Ƃ��������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
           If ���Ԃ�h�~.�S�[�� = True Then
               MsgBox ("���ǂƃS�[�������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
         End If
        If ���Ԃ�h�~.���Ƃ��� > 0 Then
           If ���Ԃ�h�~.�S�[�� = True Then
               MsgBox ("���Ƃ����ƃS�[�������Ԃ��Ă��܂�" & i & "�s�ڂł��B")
           End If
         End If
         
         If �����f���}�b�N�X < Cells(i, 2) Then
            Cells(i, 2) = Cells(i, 2) - �����f���}�b�N�X
         End If
         
         If �ǃ��f���}�b�N�X < Cells(i, 1) Then
            Cells(i, 1) = Cells(i, 1) - �ǃ��f���}�b�N�X
         End If
         
         '�ǕύX
         Const �ǖ��� As Integer = 0
         Const �ʏ�� As Integer = 1
         If ���Ԃ�h�~.�h�A = True Then
            Cells(i, 1) = �ʏ��
         ElseIf 0 < ���Ԃ�h�~.�y���f������ Then
            Cells(i, 1) = �ǖ���
         ElseIf ���Ԃ�h�~.���� = True Then
            Cells(i, 1) = �ʏ��
         ElseIf 0 < ���Ԃ�h�~.�S�[�� Then
            Cells(i, 1) = �ʏ��
         ElseIf 0 = Cells(i, 1) Then
            Cells(i, 1) = �ʏ��
         End If
         '�����y���p�̃��f�����ǂ���
         '�ǂ̍ő吔�����̒l�ɉ����邱�Ƃŕω�
         If 0 = Cells(i - 1, 1) Then
            Cells(i, 1) = Cells(i, 1) + �ǃ��f���}�b�N�X
         End If
         If 0 < ���Ԃ�h�~.�y���f������ Then
            Cells(i, 1) = �ǖ���
         End If
         
         '���ύX
         Const ������ As Integer = 0
         Const �ʏ폰 As Integer = 1
         Const �������� As Integer = 2
         Const �������E As Integer = 3
         Const ���� As Integer = 4
         
         If 0 < ���Ԃ�h�~.�G Then
            Cells(i, 2) = �ʏ폰
         ElseIf 0 < ���Ԃ�h�~.�ۏ� Then
             Cells(i, 2) = 0
         ElseIf ���Ԃ�h�~.�l�p�� = True Then
             Cells(i, 2) = 0
         ElseIf ���Ԃ�h�~.�h�A = True Then
             Cells(i, 2) = �ʏ폰
         ElseIf 0 < ���Ԃ�h�~.�y���f������ Then
            If 0 < Cells(i, 2) Then
                Cells(i, 2) = ����
            End If
         ElseIf ���Ԃ�h�~.���� = True Then
            Cells(i, 2) = �ʏ폰
         ElseIf 0 < ���Ԃ�h�~.���Ƃ��� Then
            Cells(i, 2) = ������
         ElseIf 0 < ���Ԃ�h�~.�S�[�� Then
            Cells(i, 2) = ������
         ElseIf 4 = Cells(i, 2) Then
            Cells(i, 2) = �ʏ폰
         End If
         
         '�����y���p�̃��f�����ǂ���
         '���̍ő吔�����̒l�ɉ����邱�Ƃŕω�
         If 0 = Cells(i - 1, 2) Then
            If 0 <> Cells(i, 2) Then
                Cells(i, 2) = Cells(i, 2) + �����f���}�b�N�X
            End If
         End If
         If �������� = Cells(i - 1, 2) Then
            If �������� <> Cells(i, 2) Then
                If 0 <> Cells(i, 2) Then
                    Cells(i, 2) = Cells(i, 2) + �����f���}�b�N�X
                End If
            End If
         End If
         If �������E = Cells(i - 1, 2) Then
            If �������E <> Cells(i, 2) Then
                If 0 <> Cells(i, 2) Then
                    Cells(i, 2) = Cells(i, 2) + �����f���}�b�N�X
                End If
            End If
         End If
         
         '�ǂ�
         If Cells(i, 1).Value > 0 Then
            ���Ԃ�h�~.�� = True
         Else
            ���Ԃ�h�~.�� = False
         End If
           
         '����
         If Cells(i, 2).Value > 0 Then
            ���Ԃ�h�~.�� = True
         Else
            ���Ԃ�h�~.�� = False
         End If
                      
          '�F�ς��͍Ō��
         If ���Ԃ�h�~.�� = True Then
            Cells(i, 1).Interior.Color = 46
         End If
         
         If ���Ԃ�h�~.�� = True Then
            Cells(i, 2).Interior.Color = 46
         End If
         
         If 0 < ���Ԃ�h�~.�G Then
             Cells(i, 3).Interior.Color = 46
             'Cells(i, 3) = 150
             ���Ԃ�h�~.�G = ���Ԃ�h�~.�G - 1
         End If
         
         If 0 < ���Ԃ�h�~.�ۏ� Then
             Cells(i, 4).Interior.Color = 46
             ���Ԃ�h�~.�ۏ� = ���Ԃ�h�~.�ۏ� - 1
         End If
         
         If ���Ԃ�h�~.�l�p�� Then
             Cells(i, 5).Interior.Color = 46
         End If
         
         If ���Ԃ�h�~.�h�A = True Then
             Cells(i, 6).Interior.Color = 46
         End If
         
         If 0 < ���Ԃ�h�~.�y���f������ Then
             Cells(i, 7).Interior.Color = 46
             ���Ԃ�h�~.�y���f������ = 0
         End If
         
         If ���Ԃ�h�~.���� = True Then
             Cells(i, 8).Interior.Color = 46
         End If
           
         If ���Ԃ�h�~.���� = True Then
             Cells(i, 9).Interior.Color = 46
         End If
     
         If 0 < ���Ԃ�h�~.���Ƃ��� Then
             Cells(i, 10).Interior.Color = 46
             ���Ԃ�h�~.���Ƃ��� = ���Ԃ�h�~.���Ƃ��� - 1
         End If
         
         If ���Ԃ�h�~.�S�[�� = True Then
             Cells(i, 11).Interior.Color = 46
         End If
    
         
    Next i
       
End Sub
