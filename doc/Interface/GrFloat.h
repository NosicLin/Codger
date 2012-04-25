struct GrFloat
{
	GR_INHRIT_GROBJECT;
	float f_value;
};

GrFloat* GrFloat_New(float value);
GrFloat* GrFloat_FromStr(const char* str);

GrFloat* GrFloat_Free(GrFloat*);

float GrFloat_GetValue(GrFloat* i);

GrString* GrFloat_ToGrString(GrFloat* i);
GrLong* GrFloat_ToGrLong(GrFloat*);
GrFloat* GrFloat_ToGrInt(GrFloat*);

GrFloat* GrFloat_Positive(GrFloat*);
GrFloat* GrFloat_Negative(GrFloat*);

GrFloat* GrFloat_Mul(GrFloat*,GrFloat*);
GrFloat* GrFloat_Div(GrFloat*,GrFloat*);
GrFloat* GrFloat_Mod(GrFloat*,GrFloat*);
GrFloat* GrFloat_Plus(GrFloat*,GrFloat*);
GrFloat* GrFloat_Minus(GrFloat*,GrFloat*);

int GrFloat_Cmp(GrFloat*,GrFloat*,int op);
int GrFloat_Bool(GrFloat*);


int GrFloat_Verify(GrObject*);

