//#include "bsa.h"
//#include "bsae.h"

#include <stdio.h>

#include "b23c#hlp.h"

#include <stdio.h>
#include <string.h>



/*===================================================================*/
/*               D E F I N E S  /  S T R U C T U R E S               */
/*===================================================================*/

/* work area for command parser */
BQS_WORK *bqspwrk = NULL;

/* global vars */
_CMD_GLOB   cmd_glob;

#define CAPI_SWITCH_ACEE_ENQ_NAME   "CAPI_SWITCH_ACEE"

#define MAX_REV_RECS        4096
#define MAX_REV_REC_SIZE    4*1024*1024

int  revRecs = 0;
int  revRecsFirst;
int  revRecsFull;
char revRecsRingBuf[MAX_REV_REC_SIZE];
char *revRecsRingPtr[MAX_REV_RECS+1];
int  revRecsRingPtrNxt;
int  revRecsRingPtrEnd;


/*===================================================================*/
/*                       F U N C T I O N S                           */
/*===================================================================*/


BQLONLOP *bql_open(char *openstr, char *dmsk, int conv, char ie, char *trace, void *ptcpacc)
{
	return NULL;
}

int DoInfoCmd(BQLONLOP *ponlop, RECORD_TABLE(**Table)[], void* x, void*y, void*z, void*zz, char *cmd)
{
	return -1;
}

char *FieldInfoAddr(RECORD_TABLE(*Table)[], char *FieldName)
{
	return NULL;
}

void bss_msgl(char *str, void *value, int len)
{

}

BQS_WORK *initBQS(char *pCmd, int lCmd)
{
	return NULL;
}
void freeBQS(BQS_WORK **bqspwrk)
{

}




int isTrace(void)
{
	return 0;
}

int selectAll(char *string_with_wildcards)
{
    if (!string_with_wildcards) return 1;
    if (!*string_with_wildcards) return 1;
    if (string_with_wildcards[0] == '*' && string_with_wildcards[1] == 0) return 1;
    /* caller should use string_with_wildcards for database select */
    return 0;
}


char *stripStrbuf(char *dest, int destsize, char *src)
{
    int i;

    if (destsize <= 0) return NULL;
    if (!dest) return NULL;
    if (!src)
    {
        *dest = 0;
        return dest;
    }

    strncpy(dest, src, destsize-1);
    dest[destsize-1] = 0;

    for (i = destsize-2; i >= 0; i--)
    {
        if (dest[i] == ' ')
            dest[i] = 0;
        else
            break;
    }

    return dest;
}


char *trimUTF8string(char *str)
{
    char *pstr;

    if (!str) return NULL;

    /* remove "20" (utf8 blanks) from string */
    pstr = str;
    while (*pstr)
    {
        if (*pstr == '2')
        {
            pstr++;
            if (!*pstr) break;
            if (*pstr == '0')
            {
                pstr--;
                *pstr = 0;
                break;
            }
            else
            {
                pstr++;
            }
        }
        else
        {
            pstr++;
            if (!*pstr) break;
            pstr++;
        }
    }

    return str;
}


char *findStrInBuf(char *buf, int len, char *sstr)
{
    int slen;
    int i;

    if (!buf || !sstr) return NULL;
    if (len<=0) return NULL;
    slen = strlen(sstr);
    if (slen <= 0) return buf;

    for (i = 0; i <= len - slen; i++)
    {
        if (memcmp(buf+i, sstr, slen) == 0)
        {
            return (buf+i);
        }
    }

    return NULL;
}


char *findStr(char *src, char *sstr)
{
    if (!src || !sstr) return NULL;

    return findStrInBuf(src, strlen(src), sstr);
}


char *buf2upr(char *buf, int len)
{
    int i;

    if (buf)
    {
        for (i = 0; i < len; i++)
        {
#ifdef __C370__
            if(((buf[i] >= 'a') AND (buf[i] <= 'i'))
            OR((buf[i] >= 'j') AND (buf[i] <= 'r'))
            OR((buf[i] >= 's') AND (buf[i] <= 'z')))
            {
                /* make uppercase */
                buf[i]+=0x40;
            }
#else
            buf[i] = toupper(buf[i]);
#endif
        }
    }

    return buf;
}


char *str2upr(char *str)
{
    if (!str) return NULL;
    return buf2upr(str, strlen(str));
}


/* get date (max. char 10, using cmd_glob.dmsk) and time (char 8, hour:min:sec) */
void getDateTimeHMS(char *date, char *time)
{
}


/* --------------------------------------------------------------------
 */
static int min(int a, int b)
{
    return (a < b) ? a: b;
}

/* --------------------------------------------------------------------
 */
static int max(int a, int b)
{
    return (a > b) ? a: b;
}

int memsetHexString(char *dst, char src, int dstlen)
{
    return 0;
}


int convBuffer2HexString(char *dst, char *src, int srclen)
{
    return 0;
}


int convHexString2Buffer(char *dst, char *src, int srclen)
{
    return 0;
}


int extractCSV(char *dest, int fsize, int fmax, char *src)
{
    int  cnt = 0;
    char *sn;
    int  len;

    memset(dest, 0, fsize * fmax);

    while (*src) {
        if (cnt > fmax)
        {
            /* more than max CSV elements given */
            return -1;
        }

        sn = findStr(src, ",");
        if (!sn)
        {
            /* last csv element */
            sn = src + strlen(src);
        }

        /* ignore blanks before */
        while (src < sn)
        {
            if (*src != ' ') break;
            src++;
        }
        len = sn - src;

        /* ignore blanks after */
        while (len > 0)
        {
            if (src[len-1] != ' ') break;
            len--;
        }

        /* copy CSV element */
        if (len > 0)
        {
            if (len >= fsize)
            {
                /* CSV element to large */
                return -1;
            }
            else
            {
                memcpy(&dest[cnt*fsize], src, len);
            }
        }

        /* next CSV element */
        if (*sn) sn++;
        src = sn;
        cnt++;
    }

    return cnt;
}


int countUsedFields(_CMD_FIELD *cmd_field)
{
    return 0;
}


void initFieldInfo(_FIELD_INFO *finf, int numfields)
{
    /* allocate memory for field information */
}


void addFieldInfo(_FIELD_INFO *finf, char *field_name, int value_len, char fmti, char *long_name)
{
}


void freeFieldInfo(_FIELD_INFO *finf)
{
}


void addFieldInfoEx(_FIELD_INFO *finf, _CMD_FIELD *cmd_field)
{
    _CMD_FIELD *cf;

    cf = cmd_field;

    switch (cf->fmti)
    {
        case 'I': /* INT (4 BYTE) */
            addFieldInfo(finf, cf->name, cf->size, 'I', cf->lname);
            break;
        case 'S': /* SHORT INT (2 BYTE) */
            addFieldInfo(finf, cf->name, cf->size, 'S', cf->lname);
            break;
        case 'D': /* DATE */
            addFieldInfo(finf, cf->name, cf->size, 'D', cf->lname);
            break;
        case 'T': /* TIME */
            addFieldInfo(finf, cf->name, cf->size, 'T', cf->lname);
            break;
        case '6': /* BINARY DATA (UTF) IN READABLE HEX */
            addFieldInfo(finf, cf->name, cf->size, '6', cf->lname);
            break;
        default: /* TEXT */
            addFieldInfo(finf, cf->name, cf->size, 'C', cf->lname);
            break;
    }
}


int setupFieldInfo(_FIELD_INFO *finf, _CMD_FIELD *cmd_field)
{
    return 0;
}


int sendFieldInfo(_FIELD_INFO *finf)
{
}


void setRecordDataString(_FIELD_INFO *finf, char *pRecord, int id, char *datastr)
{
	printf(datastr);
}

void setRecordDataInt(_FIELD_INFO *finf, char *pRecord, int id, int dataint)
{
	printf("%d", dataint);
}

void setRecordDataYesNoFlag(_FIELD_INFO *finf, char *pRecord, int id, char yesnoflag)
{
	if ((yesnoflag == 'Y') || (yesnoflag == 'y')) printf("Y"); else printf("N");
}


void initRevRecs(int reverse)
{
    /* init reverse order flags */
    revRecs = reverse;
    revRecsFirst = 1;
    revRecsFull = 0;
}


int sendRecord(char *pRecord, int lRecord)
{
    return 0;
}


int flushRecords()
{
    return 0;
}


int sendFieldData(_FIELD_INFO *finf, _CMD_FIELD *cmd_field)
{
	_CMD_FIELD *root = NULL;
	_CMD_FIELD *cf;
	int fc, fcn;

	char    ret_rec[32000];
	int     record_len;
	int     pos = 0;

	record_len = finf->pos;
	if (record_len > sizeof(ret_rec)) return -1;

	memset(ret_rec, ' ', record_len);

	/* searching root field */
	cf = cmd_field;
	while (cf->name[0])
	{
		if (cf->prev == NULL)
		{
			root = cf;
			break;
		}
		cf++;
	}

	/* go through list */
	cf = root;
	fcn = strlen(cmd_glob.fields_flg);
	if (fcn <= 0)
	{
		while (cf)
		{
			printf("%s=", cf->name);

			switch (cf->fmti)
			{
			case 'I':
				setRecordDataInt(finf, ret_rec, pos, *((int*)cf->pvalue));
				break;
			case 'S':
				setRecordDataInt(finf, ret_rec, pos, *((unsigned short*)cf->pvalue));
				break;
			case 'Q':
				setRecordDataYesNoFlag(finf, ret_rec, pos, *((char*)cf->pvalue));
				break;
			default:
				setRecordDataString(finf, ret_rec, pos, (char*)cf->pvalue);
				break;
			}

			printf("\n");

			pos++;

			cf = cf->next;
		}
	}
	else
	{
		for (fc = 0; fc < fcn; fc++)
		{
			if (cmd_glob.fields_flg[fc] == 0x01)
			{
				if (cf)
				{
					printf("%s=", cf->name);

					switch (cf->fmti)
					{
					case 'I':
						setRecordDataInt(finf, ret_rec, pos, *((int*)cf->pvalue));
						break;
					case 'S':
						setRecordDataInt(finf, ret_rec, pos, *((unsigned short*)cf->pvalue));
						break;
					case 'Q':
						setRecordDataYesNoFlag(finf, ret_rec, pos, *((char*)cf->pvalue));
						break;
					default:
						setRecordDataString(finf, ret_rec, pos, (char*)cf->pvalue);
						break;
					}

					printf("\n");

					pos++;

					cf = cf->next;
				}
			}
			else
			{
				/* in compatibility mode we have to fill an return field "" (empty string) which is not defined */
				setRecordDataString(finf, ret_rec, pos, "");

				pos++;
			}
		}
	}

	/* we have NO fields!!! */
	if (pos <= 0) return 0;

	return sendRecord(ret_rec, record_len);
}


int sendBuffer(char *pBuffer, int lBuffer)
{
    return 0;
}


int sendErrorInfo(unsigned short int irc, char *funcname, char *reason, char *field)
{
    return 0;
}


int sendErrorInfoOutOfMemory(_CMD *cmd, int required_size)
{
    char reason[128];
    char field[128];

    sprintf(reason, "OUT OF MEMORY");
    sprintf(field , "%d BYTES REQUESTED", required_size);
    return sendErrorInfo(0, cmd->name, reason, field);
}


int sendErrorInfoSRQE(_CMD *cmd, int irc, char *ssid, char *rtr, int wqerc, int wqeirc)
{
    char reason[128];
    char field[128];

    sprintf(reason, "SRQE TO %s/%s FAILED", ssid, rtr);
    sprintf(field , "WQERC(%d) WQEIRC(%d)", wqerc, wqeirc);
    return sendErrorInfo(irc, cmd->name, reason, field);
}


int sendErrorInfoOnlOpen(_CMD *cmd, char *ssid)
{
    char reason[128];
    char field[128];

    sprintf(reason, "ONL OPEN FAILED");
    sprintf(field , "USED SSID %s", ssid);
    return sendErrorInfo(0, cmd->name, reason, field);
}


int sendErrorInfoInsert(_CMD *cmd, BQLONLOP *ponlop, char *table)
{
	return 0;
}


int sendErrorInfoUpdate(_CMD *cmd, BQLONLOP *ponlop, char *table)
{
	return 0;
}


int sendErrorInfoDelete(_CMD *cmd, BQLONLOP *ponlop, char *table)
{
	return 0;
}


int sendErrorInfoSelect(_CMD *cmd, BQLONLOP *ponlop, char *table)
{
	return 0;
}


int copyParmValue(char *pstr1, int lstr1, char *pstr2)
{
    int   i;
    int   j;
    int   i_start;
    int   i_end;

    *pstr1 = 0;
    j = strlen(pstr2);
    for (i=0; i<j; i++) { if (*(pstr2+i)!=' ') break; }

    /* empty parameter value */
    if (i == j) return 0;

    i_start=i;
    for (i=j-1;i>=0;i--) { if (*(pstr2+i)!=' ') break; }
    i_end=i;
    if (i_end-i_start+1 > 2)
    {
        if (*(pstr2+i_start)=='"' && *(pstr2+i_end)=='"') { i_start++; i_end--; }
        else if (*(pstr2+i_start)=='\'' && *(pstr2+i_end)=='\'') { i_start++; i_end--; }
    }

    /* parameter value to long */
    if (i_end-i_start+1 > lstr1) return -1;

    memcpy (pstr1, pstr2+i_start, i_end-i_start+1);

    return 0;
}


int checkValuesInt(int val, char *values)
{
    return 0;
}


int checkValuesDate(char *val, char *values)
{
    return 0;
}


int checkValuesTime(char *val, char *values)
{
    return 0;
}


/****************************************************************************/
/* Function checks if only valid values have been specified.                */
/* Input......: val     - to be checked csv list                            */
/*              values  - csv list with all valid values                    */
/*              chkall  - 0     - break at first error                      */
/*                        1     - check all values                          */
/*                        2     - check all values AND correct val csv str  */
/* Return.....: 0       - val string is correct                             */
/*              8       - at least one value from parameter val is invalid  */
/*              16      - all values from parameter val are invalid         */
/****************************************************************************/
int checkValuesString(char *val, char *values, int chkall)
{
    char *values_curr_val;
    char values_buf[(32+1) * CMD_MAX_VALUES];
    int values_size=32+1;
    int values_max=CMD_MAX_VALUES;
    int values_num;
    int values_c;

    char *val_curr_val;
    char val_buf[(32+1) * CMD_MAX_VALUES];
    int val_size=32+1;
    int val_max=CMD_MAX_VALUES;
    int val_num;
    int val_c;

    int check_rc;
    int num_of_invalid_vals;
    char *val_final;

    /* empty string is o.k. */
    if (!*val) return 0;

    /* extract csv values */
    values_num = extractCSV(values_buf, values_size, values_max, values);
    if (values_num < 0)
    {
        /* csv extraction error */
        /* TODO */
        return 8;
    }

    if ((values_num == 0) || ((values_num == 1) && (!*values_buf)))
    {
        /* no values given, no check is required */
        return 0;
    }

    /* extract csv val */
    val_num = extractCSV(val_buf, val_size, val_max, val);
    if (val_num < 0)
    {
        /* csv extraction error */
        /* TODO */
        return 8;
    }

    /* through all values */
    num_of_invalid_vals = 0;
    val_final = val;
    for (val_c = 0; val_c < val_num; val_c++)
    {
        check_rc = 8;
        val_curr_val = &val_buf[val_c*val_size];

        for (values_c = 0; values_c < values_num; values_c++)
        {
            values_curr_val = &values_buf[values_c*values_size];

            if (strcmp(val_curr_val, values_curr_val) == 0)
            {
                /* correct value */
                check_rc = 0;
                break;
            }
        }

        if (check_rc)
        {
            /* invalid value */
            num_of_invalid_vals++;

            if (!chkall)
                break;
        }
        else
        {
            /* valid value */
            if (chkall >= 2)
            {
                /* check all and modify given val buffer */
                if (val_final == val)
                {
                    /* first csv value */
                    strcpy(val_final, val_curr_val);
                    val_final = val_final + strlen(val_curr_val);
                }
                else
                {
                    /* append correct value */
                    strcpy(val_final, ",");
                    val_final = val_final + 1;
                    strcpy(val_final, val_curr_val);
                    val_final = val_final + strlen(val_curr_val);
                }
            }
        }
    }

    if (chkall)
    {
        /* check all values */
        if (num_of_invalid_vals >= val_num)
        {
            /* all values are invalid!!! */
            check_rc = 16;
        }
    }

    return check_rc;
}


int processParm(BQS_WORK *bqspwrk, _CMD *cmd, int *val_of_unknown_parm_set, int *all_sel_val_of_parm_invalid)
{
    return 0;
}


void sortFields(_CMD *cmd)
{
    _CMD_FIELD *cmd_field = cmd->field;
    _CMD_FIELD *root = NULL;
    _CMD_FIELD *cf = NULL;
    int i;

    /* set prev/next pointers */
    /* root->prev pointer will be set to NULL */
    /* prev/next of unused fields will point to itself */
    for (i = 0; ((cmd_field+i)->name[0]); i++)
    {
        if (((cmd_field+i)->used == 'Y') || ((cmd_field+i)->used == 'y'))
        {
            /* used field */
            if (!root)
            {
                /* first field found: set it as root */
                (cmd_field+i)->prev = NULL;
                (cmd_field+i)->next = NULL;
                root = (cmd_field+i);
            }
            else
            {
                /* next field found: search correct position in list */
                cf = root;
                while (cf)
                {
                    if ((cmd_field+i)->pos < cf->pos)
                    {
                        /* insert before */
                        cf = cf->prev;
                        break;
                    }

                    if (!cf->next) break;

                    cf = cf->next;
                }

                if (!cf)
                {
                    /* next field should be new root item */
                    (cmd_field+i)->prev = NULL;
                    (cmd_field+i)->next = root;
                    root->prev = (cmd_field+i);
                    root = (cmd_field+i);
                }
                else
                {
                    /* insert next field after current pointer */
                    (cmd_field+i)->prev = cf;
                    (cmd_field+i)->next = cf->next;
                    if (cf->next)
                        cf->next->prev = (cmd_field+i);
                    cf->next = (cmd_field+i);
                }
            }
        }
        else
        {
            /* unused field */
            (cmd_field+i)->prev = (cmd_field+i);
            (cmd_field+i)->next = (cmd_field+i);
        }
    }
}


int processFields(_CMD *cmd)
{
	_CMD_FIELD *cmd_field = cmd->field;
	int i;

	char *currField;
	char fbuf[(8 + 1) * CMD_MAX_FIELDS];
	int fsize = 8 + 1;
	int fmax = CMD_MAX_FIELDS;
	int fnum;
	int fc;

	if (!cmd_field)
	{
		/* we assume that this command is a sub command */
		/* which has NO fields and MUST NOT overwrite the global settings from parent command */
		return 0;
	}

	/* reset fields to default */
	for (i = 0; ((cmd_field + i)->name[0]); i++)
	{
		switch ((cmd_field + i)->used)
		{
		case 'y':
			(cmd_field + i)->used = 'N';
			break;
		case 'n':
			(cmd_field + i)->used = 'Y';
			break;
		default:
			break;
		}

		/* all field with pos 0, means position of occurrence */
		(cmd_field + i)->pos = 0;
	}

	/* sort default fields */
	sortFields(cmd);

	/* reset the fields flags */
	memset(cmd_glob.fields_flg, 0x00, sizeof(cmd_glob.fields_flg));

//	if (*cmd_glob.fields_csv == '*')
	{
		/* all default fields should returned */
		return 0;
	}

	/* disable all fields */
	for (i = 0; ((cmd_field + i)->name[0]); i++)
	{
		switch ((cmd_field + i)->used)
		{
		case 'Y':
			(cmd_field + i)->used = 'n';
			break;
		default:
			break;
		}
	}

	/* extract csv data */
	fnum = extractCSV(fbuf, fsize, fmax, cmd_glob.fields_csv);

	if (fnum < 0)
	{
		/* csv extraction error */
		/* TODO */
		return 8;
	}

	if ((fnum == 0) || ((fnum == 1) && (!*fbuf)))
	{
		/* no fields should returned, return only the record number */
		/* TODO */
		return 8;
	}

	/* through all requested fields */
	for (fc = 0; fc < fnum; fc++)
	{
		currField = &fbuf[fc*fsize];

		/* through all defined fields */
		for (i = 0; ((cmd_field + i)->name[0]); i++)
		{
			if (strcmp((cmd_field + i)->name, currField) == 0) break;
		}

		if ((cmd_field + i)->name[0])
		{
			/* requested field found, enable it */
			switch ((cmd_field + i)->used)
			{
			case 'N':
				(cmd_field + i)->used = 'y';
				break;
			case 'n':
				(cmd_field + i)->used = 'Y';
				break;
			case 'y':
			case 'Y':
				return sendErrorInfo(0, cmd->name, "DUPLICATE FIELD", currField);
			default:
				break;
			}

			/* set column position of field */
			(cmd_field + i)->pos = fc;

			/* mark field as known field */
			cmd_glob.fields_flg[fc] = 0x01;
		}
		else
		{
			if (cmd_glob.strict)
			{
				/* default strict mode: requested field is unknown for this command */
				return sendErrorInfo(0, cmd->name, "UNKNOWN FIELD", currField);
			}
			else
			{
				/* compatibility mode: mark field as UNKNOWN field */
				cmd_glob.fields_flg[fc] = 0xff;
			}
		}
	}

	/* finally: sort enabled fields */
	sortFields(cmd);

	return 0;
}


int checkRequiredParm(_CMD *cmd)
{
    _CMD_PARM *cmd_parm = cmd->parm;
    unsigned char *counter;
    int  i;

    for (i=0; ((cmd_parm+i)->keyw[0]); i++)
    {
        counter = (unsigned char *)(&(cmd_parm+i)->flags);
        if ((!*counter) && (cmd_parm+i)->required == 'Y')
        {
            /* required parameter not set */
            return sendErrorInfo(0, cmd->name, "REQUIRED PARAMETER NOT SET", (cmd_parm+i)->keyw);
        }
    }
    return 0;
}


int checkEmptyParm(_CMD *cmd)
{
    _CMD_PARM *cmd_parm = cmd->parm;
    unsigned char *counter;
    unsigned char *valset;
    int  i;

    for (i=0; ((cmd_parm+i)->keyw[0]); i++)
    {
        /* keyword set? */
        counter = (unsigned char *)(&(cmd_parm+i)->flags);
        if (!*counter) continue;

        /* number? */
        switch ((cmd_parm+i)->fmti)
        {
            case 'I': /* INT (4 BYTE) */
            case 'S': /* SHORT INT (2 BYTE) */

                /* value set? */
                valset = ((unsigned char *)(&(cmd_parm+i)->flags)) + 1;
                if (!*valset)
                {
                    if ((cmd_parm+i)->empty=='N')
                    {
                        /* empty value not allowed */
                        return sendErrorInfo(0, cmd->name, "EMPTY VALUE NOT ALLOWED", (cmd_parm+i)->keyw);
                    }
                }

                continue;
        }

        if ((cmd_parm+i)->empty=='N')
        {
            if (strlen((cmd_parm+i)->pvalue)==0)
            {
                /* empty value not allowed */
                return sendErrorInfo(0, cmd->name, "EMPTY VALUE NOT ALLOWED", (cmd_parm+i)->keyw);
            }
        }
    }
    return 0;
}


int checkWildcardParm(_CMD *cmd)
{
    _CMD_PARM *cmd_parm = cmd->parm;
    unsigned char *counter;
    int  i;

    for (i=0; ((cmd_parm+i)->keyw[0]); i++)
    {
        /* keyword set? */
        counter = (unsigned char *)(&(cmd_parm+i)->flags);
        if (!*counter) continue;

        /* number? */
        switch ((cmd_parm+i)->fmti)
        {
            case 'I': /* INT (4 BYTE) */
            case 'S': /* SHORT INT (2 BYTE) */
                continue;
        }

        if ((cmd_parm+i)->wildcard=='N')
        {
            if (findStr((cmd_parm+i)->pvalue, "*") || findStr((cmd_parm+i)->pvalue, "?"))
            {
                /* wildcards not allowed */
                return sendErrorInfo(0, cmd->name, "WILDCARDS NOT ALLOWED", (cmd_parm+i)->keyw);
            }
        }
    }
    return 0;
}


void printCmd(_CMD *cmd)
{
    _CMD_PARM *cmd_parm = cmd->parm;
    _CMD_FIELD *cmd_field = cmd->field;
    _CMD_FIELD *root = NULL;
    _CMD_FIELD *cf;

    unsigned char *counter;
    int  i;
    char buffer[36000];

    int len;
    char len_buffer[8+1];

    bss_msgl("7510T RC: <S>",cmd->name,strlen(cmd->name));

    for (i=0; ((cmd_parm+i)->keyw[0]); i++)
    {
        sprintf(buffer, "................................");
        memcpy(buffer, (cmd_parm+i)->keyw, strlen((cmd_parm+i)->keyw));

        switch ((cmd_parm+i)->fmti)
        {
            case 'I': /* INT (4 BYTE) */
            case 'S': /* SHORT INT (2 BYTE) */
                len = (cmd_parm+i)->size;
                break;
            default:
                len = strlen((cmd_parm+i)->pvalue);
                break;
        }

        sprintf(len_buffer, "%c(%d)", (cmd_parm+i)->fmti, len);
        memcpy(buffer+32-strlen(len_buffer) - 2, len_buffer, strlen(len_buffer));

        /* keyword set? */
        counter = (unsigned char *)(&(cmd_parm+i)->flags);
        if (*counter)
        {
            switch ((cmd_parm+i)->fmti)
            {
                case 'I': /* INT (4 BYTE) */
                    sprintf(buffer+32, "(%d)", *((int*)(cmd_parm+i)->pvalue));
                    break;
                case 'S': /* SHORT INT (2 BYTE) */
                    sprintf(buffer+32, "(%d)", *((unsigned short*)(cmd_parm+i)->pvalue));
                    break;
                default:
                    if (len <= 50)
                    {
                        sprintf(buffer+32, "(%s)", (cmd_parm+i)->pvalue);
                    }
                    else
                    {
                        memcpy(buffer+32, "(", 1);
                        memcpy(buffer+33, (cmd_parm+i)->pvalue, 50);
                        memcpy(buffer+81, "..)", 3);
                    }
                    break;
            }
        }
        else
        {
            sprintf(buffer+32, "(N/A)");
        }

        bss_msgl("7510T   <S>", buffer, strlen(buffer));
    }


    if (cmd_field)
    {
        bss_msgl("7510T   RETURN FIELDS", NULL, 0);

        /* searching root field */
        cf = cmd_field;
        while (cf->name[0])
        {
            if (cf->prev == NULL)
            {
                root = cf;
                break;
            }
            cf++;
        }

        /* go through list */
        cf = root;
        while (cf)
        {
            bss_msgl("7510T     <S>", cf->name, strlen(cf->name));

            cf = cf->next;
        }
    }
}


int countParm(_CMD_PARM *cmd_parm)
{
    int i = 0;

    while ((cmd_parm+i)->keyw[0])
    {
        i++;
    }

    return i;
}


void resetParm(_CMD_PARM *cmd_parm)
{
    int i = 0;

    while ((cmd_parm+i)->keyw[0])
    {
        (cmd_parm+i)->flags = 0;
        i++;
    }
}


int isParmSet(_CMD *cmd, void *pvalue)
{
    _CMD_PARM *cmd_parm = cmd->parm;
    unsigned char *counter;
    int  i;

    for (i=0; ((cmd_parm+i)->keyw[0]); i++)
    {
        /* find correct parm */
        if ((cmd_parm+i)->pvalue != pvalue) continue;

        /* keyword set? */
        counter = (unsigned char *)(&(cmd_parm+i)->flags);
        return (*counter);
    }

    /* parm not found */
    return 0;
}


int isParmValueSet(_CMD *cmd, void *pvalue)
{
    _CMD_PARM *cmd_parm = cmd->parm;
    unsigned char *counter;
    unsigned char *valset;
    int  i;

    for (i=0; ((cmd_parm+i)->keyw[0]); i++)
    {
        /* find correct parm */
        if ((cmd_parm+i)->pvalue != pvalue) continue;

        /* keyword set? */
        counter = (unsigned char *)(&(cmd_parm+i)->flags);
        if (!*counter)
        {
            /* parm not set */
            return 0;
        }

        /* number? */
        switch ((cmd_parm+i)->fmti)
        {
            case 'I': /* INT (4 BYTE) */
            case 'S': /* SHORT INT (2 BYTE) */

                /* value set? */
                valset = ((unsigned char *)(&(cmd_parm+i)->flags)) + 1;
                return (*valset);
        }

        if (strlen((cmd_parm+i)->pvalue) == 0)
        {
            /* string is empty */
            return 0;
        }

        /* parm value set */
        return 1;
    }

    /* parm not found */
    return 0;
}


int isFieldUsed(_CMD *cmd, void *pvalue)
{
    _CMD_FIELD *cmd_field = cmd->field;
    int  i;

    for (i=0; ((cmd_field+i)->name[0]); i++)
    {
        /* find correct field */
        if ((cmd_field+i)->pvalue != pvalue) continue;

        /* field used? */
        return (((cmd_field+i)->used == 'Y') || ((cmd_field+i)->used == 'y'));
    }

    /* field not found */
    return 0;
}


int openDefaultOnlop(_CMD *cmd, BQLONLOP **pponlop)
{
    return 0;
}


void closeOnlop(BQLONLOP **pponlop)
{
}


int switchUserACEE(void)
{
    return 0;
}


int resetUserACEE(void)
{
    return 0;
}


int initCommands()
{
	_MCMD   *mc, *me;
	_CMD    *scmd;
	int     ncmd;

	/* clear */
	memset(cmd_glob.commands, 0, sizeof(cmd_glob.commands));
	cmd_glob.num_cmds = 0;

	/* through all modules, searching for available commands */
	mc = cmd_glob.mcmd;
	me = cmd_glob.mcmd + cmd_glob.mcmd_size / sizeof(_MCMD);
	while (mc < me)
	{
		ncmd = mc->init_cmd_mod(&scmd);
		if (cmd_glob.num_cmds + ncmd > MAX_COMMANDS)
		{
			/* to many commands!!! */
			return sendErrorInfo(0, "INIT", "TOO MANY COMMANDS", "");
		}
		memcpy(&cmd_glob.commands[cmd_glob.num_cmds], scmd, sizeof(_CMD) * ncmd);
		cmd_glob.num_cmds += ncmd;
		mc++;
	}

	return 0;
}



int processCmd(char *pCmd, int lCmd)
{
	int         rc = 0;
	_CMD        *cmd;

	/* initialize description of supported commands */
	if ((rc = initCommands()))
	{
		return rc;
	}

	/* through all commands */
	cmd = cmd_glob.commands;
	while (1)
	{
		if (!cmd->name[0]) break;

		if (strcmp(cmd->name, pCmd) == 0)
		{
			/* command found */
			rc = 0;

			/* initialize command */
			if (cmd->init_func)
			{
				rc = (*cmd->init_func)(cmd);
			}

			if (rc == 0)
			{
				/* process requested fields */
				if ((rc = processFields(cmd)) == 0)
				{
					/* run command */
					if (cmd->worker_func)
					{
						rc = (*cmd->worker_func)(cmd);
					}
				}
			}

			/* command term */
			if (cmd->term_func)
			{
				(*cmd->term_func)(cmd);
			}

			return rc;
		}
	}

	return rc;
}


/* this function can only work for sub commands where the parent command runs in longfkt mode */
int processSubCmd(_CMD *parent_cmd, char *pCmd, int lCmd)
{
    return 0;
}




