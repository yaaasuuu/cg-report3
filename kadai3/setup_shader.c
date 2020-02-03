//
// setup_shader.c - シェーダセット用関数
// 注意: このファイルは変更しないで下さい
//

//
// read_shader - シェーダファイルを読み込みその配列ポインタを返す
//
char*
read_shader(
	char* filename	// [in] シェーダファイル名
)
{
	FILE* fp;
	int len;
	char* ret;

// シェーダファイルのオープン
	if((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "readfile: %s open error\n", filename);
		return NULL;
	}
// ファイル長を求める
	fseek(fp, 0L, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
// ファイル長分の文字配列を確保し読み込み(後でfreeすること)
	if((ret = malloc(len + 1)) == NULL) {
		fprintf(stderr, "readfile: %s malloc error\n", filename);
		fclose(fp);
		return NULL;
	}
	fread(ret, 1, len, fp);
	ret[len] = '\0';
// シェーダファイルのクローズ
	fclose(fp);

	return ret;
}

//
// setup_shader - 頂点/フラグメントシェーダをセットし，プログラムIDを返す
//
GLuint
setup_shader(
	char* vshaderfilename,	// [in] 頂点シェーダファイル名
	char* fshaderfilename	// [in] フラグメントシェーダファイル名
)
{
	GLuint program;	// プログラムオブジェクトID
	GLuint vshader;	// 頂点シェーダID
	GLuint fshader;	// フラグメントシェーダID
	char* shsrc;	// シェーダソースプログラム
	GLint compiled;	// シェーダのコンパイルの成否
	GLint linked;	// リンクの成否

// プログラムオブジェクトを作る
	program = glCreateProgram();

// 頂点シェーダの作成/コンパイル/アタッチ
	vshader = glCreateShader(GL_VERTEX_SHADER);
	shsrc = read_shader(vshaderfilename);
	if(shsrc == NULL) {
		glDeleteShader(vshader);
		exit(1);
	}
	glShaderSource(vshader, 1, (const GLchar **)&shsrc, NULL);
	free(shsrc);

	glCompileShader(vshader);

	glGetShaderiv(vshader, GL_COMPILE_STATUS, &compiled);
	if(!compiled) {
		GLsizei len;
		GLchar* log;
		glGetShaderiv(vshader, GL_INFO_LOG_LENGTH, &len);
		log = malloc(sizeof(GLchar) * (len + 1));
		glGetShaderInfoLog(vshader, len, &len, log);
		fprintf(stderr, "VertexShader compile error: %s\n", log);
		free(log);
		glDeleteShader(vshader);
		exit(1);
	}
	glAttachShader(program, vshader);

// フラグメントシェーダの作成/コンパイル/アタッチ
	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	shsrc = read_shader(fshaderfilename);
	if(shsrc == NULL) {
		glDeleteShader(vshader);
		glDeleteShader(fshader);
		exit(1);
	}
	glShaderSource(fshader, 1, (const GLchar **)&shsrc, NULL);
	free(shsrc);

	glCompileShader(fshader);

	glGetShaderiv(fshader, GL_COMPILE_STATUS, &compiled);
	if(!compiled) {
		GLsizei len;
		GLchar* log;
		glGetShaderiv(fshader, GL_INFO_LOG_LENGTH, &len);
		log = malloc(sizeof(GLchar) * (len + 1));
		glGetShaderInfoLog(fshader, len, &len, log);
		fprintf(stderr, "FragmentShader compile error: %s\n", log);
		free(log);
		glDeleteShader(vshader);
		glDeleteShader(fshader);
		exit(1);
	}
	glAttachShader(program, fshader);

// プログラムオブジェクトのリンク
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if(!linked) {
		GLsizei len;
		glGetProgramiv(fshader, GL_INFO_LOG_LENGTH, &len);
		GLchar* log = malloc(sizeof(GLchar) * (len + 1));
		glGetProgramInfoLog(program, len, &len, log);
		fprintf(stderr, "Shader link error: %s\n", log);
		free(log);
		glDeleteShader(vshader);
		glDeleteShader(fshader);
		exit(1);
	}
// プログラムオブジェクトのインストール
	glUseProgram(program);

	return program;
}
