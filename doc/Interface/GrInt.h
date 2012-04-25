struct GrInt
{
	GR_INHRIT_GROBJECT;
	long i_value;
};


struct GrString 
{
	GR_INHRIT_GROBJECT;
	char s_value[1];
};



GrInt* GrInt_New(long value);
GrInt* GrInt_FromStr(const char* str);


GrInt* GrInt_Free(GrInt*);

long GrInt_GetValue(GrInt* i);

GrString* GrInt_ToGrString(GrInt* i);
GrLong* GrInt_ToGrLong(GrInt*);
GrFloat* GrInt_ToGrFloat(GrInt*);

GrInt* GrInt_GetAttr(GrInt*,GrObject*);
GrInt* GrInt_SetAttr(GrInt*,GrObject*,GrObject*);

GrInt* GrInt_Positive(GrInt*);
GrInt* GrInt_Negative(GrInt*);
GrInt* GrInt_Negated(GrInt*);

GrInt* GrInt_Mul(GrInt*,GrInt*);
GrInt* GrInt_Div(GrInt*,GrInt*);
GrInt* GrInt_Mod(GrInt*,GrInt*);
GrInt* GrInt_Plus(GrInt*,GrInt*);
GrInt* GrInt_Minus(GrInt*,GrInt*);

GrInt* GrInt_LShift(GrInt*,GrInt*);
GrInt* GrInt_RShift(GrInt*,GrInt*);
GrInt* GrInt_And(GrInt*,GrInt*);
GrInt* GrInt_Xor(GrInt*,GrInt*);
GrInt* GrInt_Or(GrInt*,GrInt*);

int GrInt_Cmp(GrInt*,GrInt*,int op);
int GrInt_Bool(GrInt*);

int GrInt_Print(GrInt*,FILE* f,long flags);
ssize_t GrInt_Hash(GrInt*);



int GrInt_Verify(GrObject*)


