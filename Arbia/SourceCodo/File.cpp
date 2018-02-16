#include"File.h"
/*********************************************
*/
////�t�@�C���Ǎ��݊֐�.
clsFile::clsFile()
{
	ZeroMemory( this, sizeof( clsFile ) );
}

clsFile::~clsFile()
{
	m_Data.sDataAry.clear();
	m_Data.sDataAry.shrink_to_fit();
}

//�t�@�C����������.
void clsFile::Write( char* FilePath , char* Content ){
	ofstream ofs( FilePath );
	if (!ofs) {
		cerr << "�t�@�C���I�[�v���Ɏ��s" << endl;
		exit(1);
	}
	ofs << Content <<"\n" << endl;
}

//�t�@�C����������.
//template< class T >
void clsFile::Write( char* FilePath , vector<float> DataAry ){
	ofstream ofs( FilePath );
	if (!ofs) {
		cerr << "�t�@�C���I�[�v���Ɏ��s" << endl;
		exit(1);
	}
	for (size_t i = 0; i < DataAry.size(); i++)
	{
		ofs << DataAry[i] << "," << endl;
	}
}
void clsFile::Write( char* FilePath , vector<int> DataAry ){
	ofstream ofs( FilePath );
	if (!ofs) {
		cerr << "�t�@�C���I�[�v���Ɏ��s" << endl;
		exit(1);
	}
	for (size_t i = 0; i < DataAry.size(); i++)
	{
		ofs << DataAry[i] << "," << endl;
	}
}
void clsFile::Write( char* FilePath , vector<char*> DataAry ){
	ofstream ofs( FilePath );
	if (!ofs) {
		cerr << "�t�@�C���I�[�v���Ɏ��s" << endl;
		exit(1);
	}
	for (size_t i = 0; i < DataAry.size(); i++)
	{
		ofs << DataAry[i] << "," << endl;
	}
}

//�t�@�C����������.
void clsFile::Write( char* FilePath ,int NewLine ){
	ofstream ofs( FilePath );
	if (!ofs) {
		cerr << "�t�@�C���I�[�v���Ɏ��s" << endl;
		exit(1);
	}
	for (size_t i = 0; i < m_Data.sDataAry.size(); i++)
	{
		if ((1+i)%NewLine == 0)
		{
			ofs << m_Data.sDataAry[i] << "," << endl;
		}else{
			ofs << m_Data.sDataAry[i] << "," ;
		}
	}
}


void clsFile::Read()
{
	ifstream ifs( m_Data.sPath );
	ifstream tmp;

	vector<string>	TmpArray;
	string buf;
	long i = 0;
	//m_Data.DataAry;
	if( ifs )
    {
		switch (m_Data.en_Extension)
		{
		case Txt:
			while( true )
			{
				////txt�p.
        		getline( ifs , buf, '_' );

				//1�s�ǂݎ�����̂ŁA�C���N�������g����.
				i++;
				while( buf.find( '[' ) != buf.npos ){
					buf = ReplaceString(buf,"","[","]");
				}

				split( buf, "\n" , TmpArray );
				//NULL�`�F�b�N���Ē��g���Ȃ���΍폜.
				for (int i = TmpArray.size() - 1; i >= 0; i--)
				{
					if (TmpArray[i].empty())
					{
						TmpArray.erase(TmpArray.begin() + i );
					}
				}

				// �t�@�C�����I�[�܂ŗ�����Abreak �������s����.
				// while ���𔲂���.
				if( ifs.eof() ){
					break;
				}
			}
			TmpArray.swap(m_Data.sDataAry);
			m_Data.iLineMax = m_Data.sDataAry.size();
			break;
		case Csv:
			while( true )
			{
				//csv�p.
				getline( ifs , buf, '_' );
				while( buf.find( '[' ) != buf.npos ){
					buf = ReplaceString(buf,"","[","]");
				}
				while( buf.find( '\t' ) != buf.npos ){
					buf = ReplaceString(buf,",","\t");
				}
				while( buf.find( '\n' ) != buf.npos ){
					buf = ReplaceString(buf,",","\n");
				}
				while( buf.find( '\"' ) != buf.npos ){
					buf = ReplaceString(buf,",","\"");
				}

				split( buf, "," , TmpArray );
				// �t�@�C�����I�[�܂ŗ�����Abreak �������s����.
				// while ���𔲂���.
				if( ifs.eof() ){
					break;
				}
			}
			//NULL�`�F�b�N���Ē��g���Ȃ���΍폜.
			for (int i = TmpArray.size() - 1; i >= 0; i--)
			{
				if (TmpArray[i].empty())
				{
					TmpArray.erase(TmpArray.begin() + i );
				}
			}
			//vector��NULL�`�F�b�N.
			//if (TmpArray[0].empty())
			//{
			//	TmpArray.erase( TmpArray.begin() );
			//}

			//�g���Ă���̈�̐ߖ�erase�ł͗̈�m�ۂ������Ȃ�����.
			TmpArray.swap(m_Data.sDataAry);
			//�ő吔����.
			m_Data.iLineMax = m_Data.sDataAry.size();
			break;
		default:
			//�ǂ߂Ƃ���.
			break;
		}
    }

}

void clsFile::ExtensionJudgment()
{
	size_t PathSize = NULL;
	string tmp;
	m_Data.sPath;
	PathSize = m_Data.sPath.find(".");
	tmp = m_Data.sPath.substr(PathSize + 1, m_Data.sPath.size());

	if (tmp == "txt"){
		m_Data.en_Extension = Txt;
	}
	else if (tmp == "csv"){
		m_Data.en_Extension = Csv;
	}
	else if (tmp == "x"){
		m_Data.en_Extension = x;
	}
	else if (tmp == "X"){
		m_Data.en_Extension = x;
	}
	else if (tmp == "png"){
		m_Data.en_Extension = png;
	}
	else{
		//�G���[�i�Ή����Ă��Ȃ��j
	}
}

string clsFile::ReplaceString
(
      string String1   // �u�������Ώ�.
    , string String2   // �u����������e.
    , string String3   // �����Ώ�.
	, string String4   // ��̌����ΏۂƂ̊Ԃ�����.
)
{
	if(String4 == "NULL"){
		string::size_type  Pos( String1.find( String3 ) );

		while( Pos != string::npos )
		{
			String1.replace( Pos, String3.length(), String2 );
			Pos = String1.find( String3, Pos + String2.length() );
		}
	}
	else
	{
		string::size_type  Pos1( String1.find( String3 ) );

		string::size_type  Pos2( String1.find( String4 ) );

		string::size_type  Pos3(String1.find( String4 ) - String1.find( String3 ));

		int tmp1;
		int tmp2;
		int tmp3;

		tmp1 = String1.find( String3 );
		tmp2 = String1.find( String4 );
		tmp3 = tmp2-tmp1 + 1;
		String1.replace( tmp1, tmp3, String2 );
	}
    return String1;
}

template <typename List>
void clsFile::split( const string& s, const string& delim, List& result )
{
    result.clear();

	int tmp;

	int SizeMax;
	SizeMax = 0;

	for(int j = 0; j <s.size(); j++ )
	{
		if ( s.compare(j,1,delim) == 0 )
		{
			SizeMax++;
		}
	}

	//�ő吔+1�ł��傤�ǂ悢.
	result.reserve(SizeMax+1);

    using string = string;
    string::size_type pos = 0;

    while(pos != string::npos )
    {
        string::size_type p = s.find(delim, pos);
		if(p == string::npos)
		{
			result.push_back(s.substr(pos));
			break;
		}
		else {
			result.push_back(s.substr(pos, p - pos));
		}
        pos = p + delim.size();
    }
}

void clsFile::Init(const char* fileName)
{
	m_Data.sPath = fileName;
	ExtensionJudgment();

}
