#ifndef H_B23C_HLP
#define H_B23C_HLP

#include <stdio.h>

#define BQLONLOP void
typedef struct {
	int x;
} RECORD_TABLE;

#define BQL_ONL_CONVE 0
#define BQL_ONL_NOTRACE "NO"
#define BQL_ONL_TRACE	"YES"


BQLONLOP *bql_open(char *openstr, char *dmsk, int conv, char ie, char *trace, void *ptcpacc);

int DoInfoCmd(BQLONLOP *ponlop, RECORD_TABLE(**Table)[], void* x, void*y, void*z, void*zz, char *cmd);

char *FieldInfoAddr(RECORD_TABLE(*Table)[], char *FieldName);

void bss_msgl(char *str, void *value, int len);

typedef struct
{
	char  eye[4];
	char  *work1;
	char  *work2;
	char  *work3;
	char  *sptr;
	char  *cptr;
	char  *eptr;
	char  *vsptr;
	char  *vcptr;
	char  *veptr;
	char  *wsptr;
	char  *wcptr;
	char  *weptr;
	char  *pwrkw;
	char  *res1[4];
	long  length;
	char  keyw[32];
	char  tmpfld[4];
    char  abs;
	char  res2[23];
}  BQS_WORK;

#define BQL_ERR_NDATA 16


/*===================================================================*/
/*               D E F I N E S  /  S T R U C T U R E S               */
/*===================================================================*/

#define CMD_MAX_VALUE_LENTGH    28*1024
#define CMD_MAX_VALUES          256

typedef struct
{
    char            keyw[32+1];     /* name of parameter */
    void            *pvalue;        /* pointer to destination value */
    int             size;           /* string length of value */
    unsigned int    flags;          /* internal flags */
    char            fmti;           /* internal format: I, S, D, T, C */
    char            required;       /* parameter is required? (Y/N) */
    char            empty;          /* value can be empty? (Y/N) */
    char            wildcard;       /* wildcards allowed? (Y/N) */
    char            uprcase;        /* automatic convert to uppercase (Y/N) */
    char            values[128+1];  /* valid value list (comma separated) */
    char            desc[255+1];    /* parameter description */
} _CMD_PARM;


#define CMD_MAX_FIELD_LENTGH    32000
#define CMD_MAX_FIELDS          256

typedef struct _cmd_field
{
    char  name[8+1];                /* name of field */
    char  lname[32+1];              /* long name of field */
    char  desc[255+1];              /* field description */
    struct _cmd_field *prev;
    struct _cmd_field *next;
    void *pvalue;
    int   size;
    int   pos;
    char  fmti;
    char  used;
} _CMD_FIELD;



#define CMD_FUNCTYPE_SELECT     "S"
#define CMD_FUNCTYPE_INSERT     "I"
#define CMD_FUNCTYPE_DELETE     "D"
#define CMD_FUNCTYPE_UPDATE     "U"
#define CMD_FUNCTYPE_ACTION     "A"
#define CMD_FUNCTYPE_READ       "R"
#define CMD_FUNCTYPE_WRITE      "W"

#define CMD_SWITCH_ACEE_YES     "Y"
#define CMD_SWITCH_ACEE_NO      "N"

typedef struct _cmd
{
    char            name[32+1];         /* name of function */
    char            desc[255+1];        /* function description */
    char            avail_since[10+1];  /* available since (YYYY-MM-DD) */
    char            deprecated[1+1];    /* deprecated (Y/N) */
                                        /* if "Y", function that will no longer be available in the next releases */
    char            functype[1+1];      /* type of function */
                                        /* S - Select (e.g. BQL Select or retrieve other Status information) */
                                        /* I - Insert (e.g. BQL Insert) */
                                        /* D - Delete (e.g. Delete from BQL or Delete datasets) */
                                        /* U - Update (e.g. BQL Update) */
                                        /* A - Action (e.g. Action within product/agent, submit jobs, ...) */
                                        /* R - Read data (e.g. read from datasets, bql, spool or agent) */
                                        /* W - Write data (e.g. write to datasets, bql, spool or agent) */
    char            subfunc[1+1];       /* subfunction (Y/N) */
    char            switch_acee[1+1];   /* function requests a switch from stc acee to user acee */
    _CMD_PARM       *parm;              /* pointer to parameters */
    _CMD_FIELD      *field;             /* pointer to return fields */
    void            *area;              /* pointer to function specific work area */
    int             (*init_func)(struct _cmd *cmd);
    void            (*term_func)(struct _cmd *cmd);
    int             (*worker_func)(struct _cmd *cmd);
} _CMD;


#define BQL_ONL_RECFLD void
#define BQL_ONL_FLD void

typedef struct {
    BQL_ONL_RECFLD *precfld;
    BQL_ONL_FLD    *pofld;
    int             len;
    int             pos;
} _FIELD_INFO;


/* definition of module initializer function ***********************/
typedef struct
{
    int (*init_cmd_mod)(_CMD **scmd);
} _MCMD;

/* maximal number of commands */
#define MAX_COMMANDS    4096

/* global vars *****************************************************/
typedef struct {
    void        *ptcpacc;           /* tcp access needed for unix, is set to NULL for z/os (__C370__) */
    char        ssid[4+1];          /* SSID of this STC */
    char        target_ssid[4+1];   /* SSID of the target STC */
    char        user[8+1];          /* USER who is calling the API function */
    char        stcuser[8+1];       /* USER under which the stc is running */
    void        *pBSS;              /* communication work area */
    char        dmsk[10+1];         /* datemask from URB */
    char        encoding[32+1];     /* encoding string (target codepage) needed for iconv translation */
    char        trace[3+1];         /* trace this command to JESMSGLG */
    int         strict;             /* this flag shows, if a strict parameter and field check is to be done */
                                    /* if not set: parser runs in an compatibility mode, caller can use parameter */
                                    /* and field names which are not defined */
    unsigned    records;            /* records returned by the API function */
    /*----------------------------------------------------------------------*/
    char        fields_csv[4096];   /* comma separated list of fields to return */
    char        fields_flg[455+1];  /* string with values 0x01 or 0xff, 0xff means field is unknown */
    /*----------------------------------------------------------------------*/
    _MCMD       *mcmd;                      /* list of module initializer functions */
    int         mcmd_size;                  /* sizeof mcmd buffer */
    int         num_cmds;                   /* number of supported commands */
    _CMD        commands[MAX_COMMANDS+1];   /* description of all commands */
} _CMD_GLOB;

extern _CMD_GLOB cmd_glob;

/*===================================================================*/
/*               F U N C T I O N   P R O T O T Y P E S               */
/*===================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

	int isTrace(void);

#ifdef __cplusplus
}
#endif

int selectAll(char *string_with_wildcards);

char *stripStrbuf(char *dest, int destsize, char *src);
char *trimUTF8string(char *str);
char *findStrInBuf(char *buf, int len, char *sstr);
char *findStr(char *src, char *sstr);
char *buf2upr(char *buf, int len);
char *str2upr(char *str);
void getDateTimeHMS(char *date, char *time);

int memsetHexString(char *dst, char src, int dstlen);
int convBuffer2HexString(char *dst, char *src, int srclen);
int convHexString2Buffer(char *dst, char *src, int srclen);

int extractCSV(char *dest, int fsize, int fmax, char *src);

int countUsedFields(_CMD_FIELD *cmd_field);

void initFieldInfo(_FIELD_INFO *finf, int numfields);
void addFieldInfo(_FIELD_INFO *finf, char *field_name, int value_len, char fmti, char *long_name);
void freeFieldInfo(_FIELD_INFO *finf);
void addFieldInfoEx(_FIELD_INFO *finf, _CMD_FIELD *cmd_field);

int setupFieldInfo(_FIELD_INFO *finf, _CMD_FIELD *cmd_field);

int sendFieldInfo(_FIELD_INFO *finf);

void setRecordDataString(_FIELD_INFO *finf, char *pRecord, int id, char *datastr);
void setRecordDataInt(_FIELD_INFO *finf, char *pRecord, int id, int dataint);
void setRecordDataYesNoFlag(_FIELD_INFO *finf, char *pRecord, int id, char yesnoflag);

void initRevRecs(int reverse);
int sendRecord(char *pRecord, int lRecord);
int flushRecords();
int sendFieldData(_FIELD_INFO *finf, _CMD_FIELD *cmd_field);

int sendBuffer(char *pBuffer, int lBuffer);

int sendErrorInfo(unsigned short int irc, char *funcname, char *reason, char *field);
int sendErrorInfoOutOfMemory(_CMD *cmd, int required_size);
int sendErrorInfoSRQE(_CMD *cmd, int irc, char *ssid, char *rtr, int wqerc, int wqeirc);
int sendErrorInfoOnlOpen(_CMD *cmd, char *ssid);
int sendErrorInfoInsert(_CMD *cmd, BQLONLOP *ponlop, char *table);
int sendErrorInfoUpdate(_CMD *cmd, BQLONLOP *ponlop, char *table);
int sendErrorInfoDelete(_CMD *cmd, BQLONLOP *ponlop, char *table);
int sendErrorInfoSelect(_CMD *cmd, BQLONLOP *ponlop, char *table);

BQS_WORK *initBQS(char *pCmd, int lCmd);
void freeBQS(BQS_WORK **bqspwrk);
int copyParmValue(char *pstr1, int lstr1, char *pstr2);
int checkValuesInt(int val, char *values);
int checkValuesDate(char *val, char *values);
int checkValuesTime(char *val, char *values);
int checkValuesString(char *val, char *values, int chkall);
int processParm(BQS_WORK *bqspwrk, _CMD *cmd, int *val_of_unknown_parm_set, int *all_sel_val_of_parm_invalid);
void sortFields(_CMD *cmd);
int processFields(_CMD *cmd);
int checkRequiredParm(_CMD *cmd);
int checkEmptyParm(_CMD *cmd);
int checkWildcardParm(_CMD *cmd);
void printCmd(_CMD *cmd);

int countParm(_CMD_PARM *cmd_parm);
void resetParm(_CMD_PARM *cmd_parm);
int isParmSet(_CMD *cmd, void *pvalue);
int isParmValueSet(_CMD *cmd, void *pvalue);

int isFieldUsed(_CMD *cmd, void *pvalue);

int openDefaultOnlop(_CMD *cmd, BQLONLOP **pponlop);
void closeOnlop(BQLONLOP **pponlop);


int initCommands();
int processCmd(char *pCmd, int lCmd);
int processSubCmd(_CMD *parent_cmd, char *pCmd, int lCmd);




#endif   /* H_B23C_HLP */

