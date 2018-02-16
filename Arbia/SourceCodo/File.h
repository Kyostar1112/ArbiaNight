
#ifndef _FILE_H_
#define _FILE_H_
#include <iostream>
#include <Shlwapi.h>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include"MyMacro.h"

using namespace std;
enum Extension
{
	Txt = 0,	//�e�L�X�g�t�@�C��.
	Csv,		//Csv�t�@�C��.
	x,			//X�t�@�C��.
	png,		//png�t�@�C��.
};
struct FileSet
{
	string			sPath;			//�t�@�C���p�X.
	Extension		en_Extension;	//�g���q����p.
	vector<string>	sDataAry;		//�f�[�^�̔z��.
	int				iLineMax;		//�z��̍ő吔.
};
class clsFile
{
public:
	clsFile();
	~clsFile();

	//�ŏ��ɒʂ���.
	void Init( const char* fileName );

	//�t�@�C����������.
	void Write( char* FilePath_A , char* FilePath );

	//�t�@�C����������.
	void Write( char* FilePath , int NewLine = NULL );

	//�t�@�C����������.
	//template< class T >
	void Write( char* FilePath , vector<float> DataAry );
	void Write( char* FilePath , vector<int> DataAry );
	void Write( char* FilePath , vector<char*> DataAry );

	//�t�@�C���Ǎ�.
	void Read();

	//�t�@�C�����J��(Txt,Csv�̂�).
	inline void Open( HWND hWnd ){
		ShellExecute(hWnd, NULL, m_Data.sPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}

	//�z��̍ő吔.
	inline int GetDataArrayNumMax( ){
		return m_Data.iLineMax;
	}

	//�g���q���ǂꂩ.
	inline Extension GetExtension( ){
		return m_Data.en_Extension;
	}

	//�g���q���ǂꂩ.
	inline string GetFilePath( ){
		return m_Data.sPath;
	}

	//float�^�ŕԂ���.
	inline void GetDataArray( float& Data ,int Array_Num )
	{
		stringstream is;
		float tmp;
		is.str( m_Data.sDataAry[Array_Num] );
		is >> tmp;
		Data = tmp;
		is.clear(stringstream::goodbit);
	}

	//int�^�ŕԂ���.
	template<class T>
	inline void GetDataArray( T* Data, int Array_Num )
	{
		stringstream is;
		T tmp;
		is.str( m_Data.sDataAry[Array_Num] );
		is >> tmp;
		*Data = tmp;
		is.clear(stringstream::goodbit);
	}

	//bool�^�ŕԂ���.
	inline void GetDataArray( bool& Data, int Array_Num )
	{
		stringstream is;
		bool tmp;
		is.str( m_Data.sDataAry[Array_Num] );
		is >> tmp;
		Data = tmp;
		is.clear(stringstream::goodbit);
	}

	inline vector<int> GetDataArray()
	{
		vector<int> Tmp;
		Tmp.resize(m_Data.sDataAry.size());
		for (size_t i = 0; i < m_Data.sDataAry.size(); i++)
		{
			Tmp[i] = stoi(m_Data.sDataAry[i]);
		}
		return Tmp;
	}

	//char*�^�ŕԂ���.
	inline char* GetDataArray( int Array_Num )
	{
		return (char*)m_Data.sDataAry[Array_Num].c_str();
	}

private:

	//������u��.
	string ReplaceString
	(
		  string String1   // �u�������Ώ�.
		, string String2   // �u����������e.
		, string String3   // �����Ώ�.
		, string String4 = "NULL"   // ��̌����ΏۂƂ̊Ԃ�����.
	);

	template <typename List>
	void split(const std::string& s, const std::string& delim, List& result);

	//�g���q���o����(string�^�̂�).
	void ExtensionJudgment();

	FileSet	m_Data;

};


#endif