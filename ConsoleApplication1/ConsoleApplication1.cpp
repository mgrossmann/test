#include "stdafx.h"

#include <stdio.h>
#include <string.h>

extern "C" {
#include "b23c#hlp.h"
#include "b23c#def.h"
}

/* Version identifier **********************************************/
#define VID_CMDCL_DATASRC   "datasrc"
#define VID_CMDCL_TYPE      "systype"
#define VID_CMDCL_TITLE     "system title"
#define VID_CMDCL_VERSION   "V2.1"
#define VID_CMDCL_BUILD     "22090"

/*-----------------------------------------------------------------*/
/*-----------------------------------------------------------------*/

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/* Command: VERSION_GET working storage ****************************/
typedef struct
{
	/* parameter area */

	/* field area */
	char f_datasrc[8 + 1];
	char f_type[8 + 1];
	char f_title[64 + 1];
	char f_version[8 + 1];
	char f_build[8 + 1];
	char f_sysname[8 + 1];
	char f_syslvl[8 + 1];
	char f_sysptf[8 + 1];
	char f_bsalvl[8 + 1];
	char f_bsaptf[8 + 1];

	/* working storage */
	_FIELD_INFO     finf;
	BQLONLOP        *ponlop;

} _CMD_VERSION_GET;

_CMD_VERSION_GET    cmd_version_get;
/*-----------------------------------------------------------------*/
/* Command: VERSION_GET parameter description **********************/
/* --PARMNAME----VALUE STRING BUFFER----------MAX STRING LENGTH-----------------------C--FoI---R----E----W----U-- */
/* ---VALID VALUES----------------------------------------------------------------------------------------------- */
/* ----DESCRIPTION----------------------------------------------------------------------------------------------- */
_CMD_PARM   cmd_version_get_parm[] = {
	"",0,0,0,0,0,0,0,0,
	"",
	""
};
/*-----------------------------------------------------------------*/
/* Command: VERSION_GET field description **************************/
/* --FLDNAME----LONG NAME-------------------------DESCRIPTION----------------------------------------- */
/* -------------VALUE STRING BUFFER---------------MAX STRING LENGTH (external)-----------POS-FoI---U-- */
_CMD_FIELD  cmd_version_get_field[] = {
	"DATASRC",  "Data_Source"                   , "",
	NULL, NULL, cmd_version_get.f_datasrc       , sizeof(cmd_version_get.f_datasrc) - 1   , 0, 'C', 'Y',
	"TYPE",     "Backend_Type"                  , "",
	NULL, NULL, cmd_version_get.f_type          , sizeof(cmd_version_get.f_type) - 1      , 0, 'C', 'Y',
	"TITLE",    "Title"                         , "",
	NULL, NULL, cmd_version_get.f_title         , sizeof(cmd_version_get.f_title) - 1     , 0, 'C', 'Y',
	"VERSION",  "Version"                       , "",
	NULL, NULL, cmd_version_get.f_version       , sizeof(cmd_version_get.f_version) - 1   , 0, 'C', 'Y',
	"BUILD",    "Build_Level"                   , "",
	NULL, NULL, cmd_version_get.f_build         , sizeof(cmd_version_get.f_build) - 1     , 0, 'C', 'Y',
	"SYSNAME",  "System_Name"                   , "",
	NULL, NULL, cmd_version_get.f_sysname       , sizeof(cmd_version_get.f_sysname) - 1   , 0, 'C', 'Y',
	"SYSLVL",   "System_Level"                  , "",
	NULL, NULL, cmd_version_get.f_syslvl        , sizeof(cmd_version_get.f_syslvl) - 1    , 0, 'C', 'Y',
	"SYSPTF",   "System_PTF_Level"              , "",
	NULL, NULL, cmd_version_get.f_sysptf        , sizeof(cmd_version_get.f_sysptf) - 1    , 0, 'C', 'Y',
	"BSALVL",   "System_BSA_Level"              , "",
	NULL, NULL, cmd_version_get.f_bsalvl        , sizeof(cmd_version_get.f_bsalvl) - 1    , 0, 'C', 'Y',
	"BSAPTF",   "System_BSA_PTF_Level"          , "",
	NULL, NULL, cmd_version_get.f_bsaptf        , sizeof(cmd_version_get.f_bsaptf) - 1    , 0, 'C', 'Y',
	"","","",
	NULL,NULL,0,0,0,0,0
};
/*-----------------------------------------------------------------*/
/* Command: VERSION_GET function prototypes ************************/
int cmd_version_get_init(struct _cmd *cmd);
void cmd_version_get_term(struct _cmd *cmd);
int cmd_version_get_worker(struct _cmd *cmd);
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

/*-----------------------------------------------------------------*/

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/* Command: FUNCTION_LST working storage ***************************/
typedef struct
{
	/* parameter area */

	/* field area */
	char f_funcname[32 + 1];      /* name of function */
	char f_desc[255 + 1];         /* function description */
	char f_avail_since[10 + 1];   /* available since (YYYY-MM-DD) */
	char f_deprecated[1 + 1];     /* deprecated (Y/N) */
								  /* if "Y", function that will no longer be available in the next releases */
	char f_functype[1 + 1];       /* type of function */
								  /* S - Select (e.g. BQL Select or retrieve other Status information) */
								  /* I - Insert (e.g. BQL Insert) */
								  /* D - Delete (e.g. Delete from BQL or Delete datasets) */
								  /* U - Update (e.g. BQL Update) */
								  /* A - Action (e.g. Action within product/agent, submit jobs, ...) */
								  /* R - Read data (e.g. read from datasets, bql, spool or agent) */
								  /* W - Write data (e.g. write to datasets, bql, spool or agent) */
	char f_subfunc[1 + 1];        /* subfunction (Y/N) */

								  /* working storage */
	_FIELD_INFO     finf;

} _CMD_FUNCTION_LST;

_CMD_FUNCTION_LST   cmd_function_lst;
/*----------------------------------------------------------------*/
/* Command: FUNCTION_LST parameter description *********************/
/* --PARMNAME----VALUE STRING BUFFER----------MAX STRING LENGTH-----------------------C--FoI---R----E----W----U-- */
/* ---VALID VALUES----------------------------------------------------------------------------------------------- */
/* ----DESCRIPTION----------------------------------------------------------------------------------------------- */
_CMD_PARM   cmd_function_lst_parm[] = {
	"",0,0,0,0,0,0,0,0,
	"",
	""
};
/*-----------------------------------------------------------------*/
/* Command: FUNCTION_LST field description *************************/
/* --FLDNAME----LONG NAME-------------------------DESCRIPTION--------------------------------------------- */
/* -------------VALUE STRING BUFFER---------------MAX STRING LENGTH (external)---------------POS-FoI---U-- */
_CMD_FIELD  cmd_function_lst_field[] = {
	"FUNCNAME", "FUNCTION_NAME"                 , PAFIDESC_FUNCTION_NAME,
	NULL, NULL, cmd_function_lst.f_funcname     , sizeof(cmd_function_lst.f_funcname) - 1     , 0, 'C', 'Y',
	"AVSINCE",  "AVAILABLE_SINCE"               , PAFIDESC_FUNCTION_AVAILABLE_SINCE,
	NULL, NULL, cmd_function_lst.f_avail_since  , sizeof(cmd_function_lst.f_avail_since) - 1  , 0, 'C', 'Y',
	"DEPRECAT", "DEPRECATED"                    , PAFIDESC_FUNCTION_DEPRECATED,
	NULL, NULL, cmd_function_lst.f_deprecated   , sizeof(cmd_function_lst.f_deprecated) - 1   , 0, 'C', 'Y',
	"FUNCTYPE", "FUNCTION_TYPE"                 , PAFIDESC_FUNCTION_TYPE,
	NULL, NULL, cmd_function_lst.f_functype     , sizeof(cmd_function_lst.f_functype) - 1     , 0, 'C', 'N',
	"SUBFUNC",  "SUBFUNCTION"                   , PAFIDESC_FUNCTION_SUBFUNCTION,
	NULL, NULL, cmd_function_lst.f_subfunc      , sizeof(cmd_function_lst.f_subfunc) - 1      , 0, 'C', 'N',
	"DESC",     "DESCRIPTION"                   , PAFIDESC_FUNCTION_DESCRIPTION,
	NULL, NULL, cmd_function_lst.f_desc         , sizeof(cmd_function_lst.f_desc) - 1         , 0, 'C', 'Y',
	"","","",
	NULL,NULL,0,0,0,0,0
};
/*-----------------------------------------------------------------*/
/* Command: FUNCTION_LST function prototypes ***********************/
int cmd_function_lst_init(struct _cmd *cmd);
void cmd_function_lst_term(struct _cmd *cmd);
int cmd_function_lst_worker(struct _cmd *cmd);
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

/*-----------------------------------------------------------------*/

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/* Command: PARAMETER_LST working storage **************************/
typedef struct
{
	/* parameter area */
	char funcname[32 + 1];

	/* field area */
	char f_parmname[32 + 1];
	int  f_length;
	char f_fmti[1 + 1];
	char f_required;
	char f_empty;
	char f_wildcard;
	char f_uprcase;
	char f_values[128 + 1];
	char f_desc[255 + 1];

	/* working storage */
	_FIELD_INFO     finf;

} _CMD_PARAMETER_LST;

_CMD_PARAMETER_LST  cmd_parameter_lst;
/*-----------------------------------------------------------------*/
/* Command: PARAMETER_LST parameter description ****************/
/* --PARMNAME----VALUE STRING BUFFER----------MAX STRING LENGTH-----------------------C--FoI---R----E----W----U-- */
/* ---VALID VALUES----------------------------------------------------------------------------------------------- */
/* ----DESCRIPTION----------------------------------------------------------------------------------------------- */
_CMD_PARM   cmd_parameter_lst_parm[] = {
	"FUNCNAME" , cmd_parameter_lst.funcname , sizeof(cmd_parameter_lst.funcname) - 1  , 0, 'C', 'Y', 'N', 'N', 'N',
	"",
	"",
	"",0,0,0,0,0,0,0,0,
	"",
	""
};
/*-----------------------------------------------------------------*/
/* Command: PARAMETER_LST field description ************************/
/* --FLDNAME----LONG NAME-------------------------DESCRIPTION----------------------------------------- */
/* -------------VALUE STRING BUFFER---------------MAX STRING LENGTH (external)-----------POS-FoI---U-- */
_CMD_FIELD  cmd_parameter_lst_field[] = {
	"PARMNAME", "Name_of_parameter"             , "",
	NULL, NULL, cmd_parameter_lst.f_parmname    , sizeof(cmd_parameter_lst.f_parmname) - 1, 0, 'C', 'Y',
	"LENGTH",   "Length"                        , "",
	NULL, NULL, &cmd_parameter_lst.f_length     , 8                                     , 0, 'I', 'Y',
	"FMTI",     "Internal_format"               , "",
	NULL, NULL, cmd_parameter_lst.f_fmti        , sizeof(cmd_parameter_lst.f_fmti) - 1    , 0, 'C', 'Y',
	"REQUIRED", "Required"                      , "",
	NULL, NULL, &cmd_parameter_lst.f_required   , 1                                     , 0, 'Q', 'Y',
	"EMPTY",    "Empty"                         , "",
	NULL, NULL, &cmd_parameter_lst.f_empty      , 1                                     , 0, 'Q', 'Y',
	"WILDCARD", "Wildcard"                      , "",
	NULL, NULL, &cmd_parameter_lst.f_wildcard   , 1                                     , 0, 'Q', 'Y',
	"UPRCASE",  "Uppercase"                     , "",
	NULL, NULL, &cmd_parameter_lst.f_uprcase    , 1                                     , 0, 'Q', 'Y',
	"VALUES",   "Valid_values"                  , "",
	NULL, NULL, cmd_parameter_lst.f_values      , sizeof(cmd_parameter_lst.f_values) - 1  , 0, 'C', 'Y',
	"DESC",     "Description_of_parameter"      , "",
	NULL, NULL, cmd_parameter_lst.f_desc        , sizeof(cmd_parameter_lst.f_desc) - 1    , 0, 'C', 'Y',
	"","","",
	NULL,NULL,0,0,0,0,0
};
/*-----------------------------------------------------------------*/
/* Command: PARAMETER_LST function prototypes **********************/
int cmd_parameter_lst_init(struct _cmd *cmd);
void cmd_parameter_lst_term(struct _cmd *cmd);
int cmd_parameter_lst_worker(struct _cmd *cmd);
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

/*-----------------------------------------------------------------*/

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/* Command: FIELD_LST working storage ******************************/
typedef struct
{
	/* parameter area */
	char funcname[32 + 1];

	/* field area */
	char f_fldname[8 + 1];
	char f_fldlname[32 + 1];
	int  f_length;
	char f_fmti[1 + 1];
	char f_def;
	char f_desc[255 + 1];

	/* working storage */
	_FIELD_INFO     finf;

} _CMD_FIELD_LST;

_CMD_FIELD_LST  cmd_field_lst;
/*-----------------------------------------------------------------*/
/* Command: FIELD_LST parameter description ************************/
/* --PARMNAME----VALUE STRING BUFFER----------MAX STRING LENGTH-----------------------C--FoI---R----E----W----U-- */
/* ---VALID VALUES----------------------------------------------------------------------------------------------- */
/* ----DESCRIPTION----------------------------------------------------------------------------------------------- */
_CMD_PARM   cmd_field_lst_parm[] = {
	"FUNCNAME" , cmd_field_lst.funcname     , sizeof(cmd_field_lst.funcname) - 1      , 0, 'C', 'Y', 'N', 'N', 'N',
	"",
	"",
	"",0,0,0,0,0,0,0,0,
	"",
	""
};
/*-----------------------------------------------------------------*/
/* Command: FIELD_LST field description ****************************/
/* --FLDNAME----LONG NAME-------------------------DESCRIPTION----------------------------------------- */
/* -------------VALUE STRING BUFFER---------------MAX STRING LENGTH (external)-----------POS-FoI---U-- */
_CMD_FIELD  cmd_field_lst_field[] = {
	"FLDNAME",  "Name_of_field"                 , "",
	NULL, NULL, cmd_field_lst.f_fldname         , sizeof(cmd_field_lst.f_fldname) - 1     , 0, 'C', 'Y',
	"FLDLNAME", "Long_name_of_field"            , "",
	NULL, NULL, cmd_field_lst.f_fldlname        , sizeof(cmd_field_lst.f_fldlname) - 1    , 0, 'C', 'Y',
	"LENGTH",   "Length"                        , "",
	NULL, NULL, &cmd_field_lst.f_length         , 8                                     , 0, 'I', 'Y',
	"FMTI",     "Internal_format"               , "",
	NULL, NULL, cmd_field_lst.f_fmti            , sizeof(cmd_field_lst.f_fmti) - 1        , 0, 'C', 'Y',
	"DEF",      "Available_in_default_return"   , "",
	NULL, NULL, &cmd_field_lst.f_def            , 1                                     , 0, 'Q', 'Y',
	"DESC",     "Description_of_field"          , "",
	NULL, NULL, cmd_field_lst.f_desc            , sizeof(cmd_field_lst.f_desc) - 1        , 0, 'C', 'Y',
	"","","",
	NULL,NULL,0,0,0,0,0
};
/*-----------------------------------------------------------------*/
/* Command: FIELD_LST function prototypes **************************/
int cmd_field_lst_init(struct _cmd *cmd);
void cmd_field_lst_term(struct _cmd *cmd);
int cmd_field_lst_worker(struct _cmd *cmd);
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

/*-----------------------------------------------------------------*/

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/* Commands supported by this module *******************************/
_CMD cmd_commands[] = {
	"VERSION_GET",
		FUNCDESC_VERSION_GET,
			"2016-03-11", "N", "S", "N", "N",
			cmd_version_get_parm,
			cmd_version_get_field,
			&cmd_version_get,
			cmd_version_get_init,
			cmd_version_get_term,
			cmd_version_get_worker,
	"FUNCTION_LST",
		FUNCDESC_FUNCTION_LST,
			"2016-03-11", "N", "S", "N", "N",
			cmd_function_lst_parm,
			cmd_function_lst_field,
			&cmd_function_lst,
			cmd_function_lst_init,
			cmd_function_lst_term,
			cmd_function_lst_worker,
	"PARAMETER_LST",
		FUNCDESC_PARAMETER_LST,
			"2016-03-11", "N", "S", "N", "N",
			cmd_parameter_lst_parm,
			cmd_parameter_lst_field,
			&cmd_parameter_lst,
			cmd_parameter_lst_init,
			cmd_parameter_lst_term,
			cmd_parameter_lst_worker,
	"FIELD_LST",
		FUNCDESC_FIELD_LST,
			"2016-03-11", "N", "S", "N", "N",
			cmd_field_lst_parm,
			cmd_field_lst_field,
			&cmd_field_lst,
			cmd_field_lst_init,
			cmd_field_lst_term,
			cmd_field_lst_worker
};
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

/*===================================================================*/
/*                       F U N C T I O N S                           */
/*===================================================================*/

int cmd_commands_get(_CMD **scmd)
{
	*scmd = cmd_commands;
	return sizeof(cmd_commands) / sizeof(_CMD);
}


/*-----------------------------------------------------------------*/


int cmd_version_get_init(struct _cmd *cmd)
{
	_CMD_VERSION_GET *_this = (_CMD_VERSION_GET*)cmd->area;
	int rc;

	/* init my working area */
	memset(_this, 0, sizeof(_CMD_VERSION_GET));

	return 0;
}


void cmd_version_get_term(struct _cmd *cmd)
{
	_CMD_VERSION_GET *_this = (_CMD_VERSION_GET*)cmd->area;

	/* free resources */
	freeFieldInfo(&_this->finf);
	closeOnlop(&_this->ponlop);
}


int cmd_version_get_worker(struct _cmd *cmd)
{
	_CMD_VERSION_GET *_this = (_CMD_VERSION_GET*)cmd->area;
	int rc = 0;

	char openstr[1024];
	char bqlcmd[32 * 1024];
	char *pbqlcmd;
	char *adrrec;

	RECORD_TABLE(*table)[] = NULL;
	int     first;

	char    *psysname;
	char    *psyslvl;
	char    *psysptf;
	char    *pbsalvl;
	char    *pbsaptf;

	psysname = NULL;
	psyslvl = NULL;
	psysptf = NULL;
	pbsalvl = NULL;
	pbsaptf = NULL;

	/* prepare record data */
	stripStrbuf(_this->f_datasrc, sizeof(_this->f_datasrc), VID_CMDCL_DATASRC);
	stripStrbuf(_this->f_type, sizeof(_this->f_type), VID_CMDCL_TYPE);
	stripStrbuf(_this->f_title, sizeof(_this->f_title), VID_CMDCL_TITLE);
	stripStrbuf(_this->f_version, sizeof(_this->f_version), VID_CMDCL_VERSION);
	stripStrbuf(_this->f_build, sizeof(_this->f_build), VID_CMDCL_BUILD);
	stripStrbuf(_this->f_sysname, sizeof(_this->f_sysname), "SYS1");
	stripStrbuf(_this->f_syslvl, sizeof(_this->f_syslvl), "V2.1");
	stripStrbuf(_this->f_sysptf, sizeof(_this->f_sysptf), "PPP1234");
	stripStrbuf(_this->f_bsalvl, sizeof(_this->f_bsalvl), "V1.1");
	stripStrbuf(_this->f_bsaptf, sizeof(_this->f_bsaptf), "XXX1234");

	/* send a record */
	if ((rc = sendFieldData(&_this->finf, cmd->field)) != 0)
	{
		return rc;
	}

	return 0;
}


/*-----------------------------------------------------------------*/


int cmd_function_lst_init(struct _cmd *cmd)
{
	_CMD_FUNCTION_LST *_this = (_CMD_FUNCTION_LST*)cmd->area;

	/* init my working area */
	memset(_this, 0, sizeof(_CMD_FUNCTION_LST));

	return 0;
}


void cmd_function_lst_term(struct _cmd *cmd)
{
	_CMD_FUNCTION_LST *_this = (_CMD_FUNCTION_LST*)cmd->area;

	/* free resources */
	freeFieldInfo(&_this->finf);
}


int cmd_function_lst_worker(struct _cmd *cmd)
{
	_CMD_FUNCTION_LST *_this = (_CMD_FUNCTION_LST*)cmd->area;

	int             rc = 0;
	_CMD            *cmdlist;

	/* setup fields to return */
	setupFieldInfo(&_this->finf, cmd->field);
	if ((rc = sendFieldInfo(&_this->finf)) != 0) return rc;

	cmdlist = cmd_glob.commands;
	while (1)
	{
		if (!cmdlist->name[0]) break;

		/* prepare record data */
		stripStrbuf(_this->f_funcname, sizeof(_this->f_funcname), cmdlist->name);
		stripStrbuf(_this->f_avail_since, sizeof(_this->f_avail_since), cmdlist->avail_since);
		stripStrbuf(_this->f_deprecated, sizeof(_this->f_deprecated), cmdlist->deprecated);
		stripStrbuf(_this->f_functype, sizeof(_this->f_functype), cmdlist->functype);
		stripStrbuf(_this->f_subfunc, sizeof(_this->f_subfunc), cmdlist->subfunc);
		stripStrbuf(_this->f_desc, sizeof(_this->f_desc), cmdlist->desc);

		/* send a record */
		if ((rc = sendFieldData(&_this->finf, cmd->field)) != 0)
		{
			return rc;
		}

		cmdlist = cmdlist + 1;
	}

	return 0;
}


/*-----------------------------------------------------------------*/


int cmd_parameter_lst_init(struct _cmd *cmd)
{
	_CMD_PARAMETER_LST *_this = (_CMD_PARAMETER_LST*)cmd->area;

	/* init my working area */
	memset(_this, 0, sizeof(_CMD_PARAMETER_LST));

	return 0;
}

void cmd_parameter_lst_term(struct _cmd *cmd)
{
	_CMD_PARAMETER_LST *_this = (_CMD_PARAMETER_LST*)cmd->area;

	/* free resources */
	freeFieldInfo(&_this->finf);
}

int cmd_parameter_lst_worker(struct _cmd *cmd)
{
	_CMD_PARAMETER_LST *_this = (_CMD_PARAMETER_LST*)cmd->area;

	int             rc = 0;
	char            ret_rec[32000];
	int             record_len;
	_CMD            *cmdlist;
	_CMD_PARM       *parm;
	char            *pos;

	/* setup fields to return */
	setupFieldInfo(&_this->finf, cmd->field);
	if ((rc = sendFieldInfo(&_this->finf)) != 0) return rc;

	cmdlist = cmd_glob.commands;
	while (1)
	{
		if (!cmdlist->name[0]) break;

		if (strcmp(cmdlist->name, _this->funcname) == 0)
		{
			/* requested function found */
			parm = cmdlist->parm;
			if (parm->keyw[0])
			{
				while (parm->keyw[0])
				{
					/* prepare record data */
					stripStrbuf(_this->f_parmname, sizeof(_this->f_parmname), parm->keyw);
					_this->f_length = parm->size;
					_this->f_fmti[0] = parm->fmti;
					_this->f_fmti[1] = 0;
					_this->f_required = parm->required;
					_this->f_empty = parm->empty;
					_this->f_wildcard = parm->wildcard;
					_this->f_uprcase = parm->uprcase;
					stripStrbuf(_this->f_desc, sizeof(_this->f_desc), parm->desc);

					if ((pos = findStr(parm->values, "%DMSK%")))
					{
						/* use global date mask */
						_this->f_values[0] = 0;
						if (pos > parm->values)
						{
							memcpy(_this->f_values, parm->values, pos - parm->values);
							_this->f_values[pos - parm->values] = 0;
						}

						strcat(_this->f_values, cmd_glob.dmsk);

						pos = pos + strlen("%DMSK%");

						if (pos - parm->values < strlen(parm->values))
						{
							strcat(_this->f_values, pos);
						}
					}
					else
					{
						stripStrbuf(_this->f_values, sizeof(_this->f_values), parm->values);
					}


					/* send a record */
					if ((rc = sendFieldData(&_this->finf, cmd->field)) != 0)
					{
						return rc;
					}

					parm++;
				}

				return rc;
			}
			else
			{
				/* function has no parameter */
				return 16;
			}
		}

		cmdlist = cmdlist + 1;
	}

	return sendErrorInfo(666, cmd->name, "INVALID FUNCTION NAME", _this->funcname);
}


/*-----------------------------------------------------------------*/


int cmd_field_lst_init(struct _cmd *cmd)
{
	_CMD_FIELD_LST *_this = (_CMD_FIELD_LST*)cmd->area;

	/* init my working area */
	memset(_this, 0, sizeof(_CMD_FIELD_LST));

	return 0;
}

void cmd_field_lst_term(struct _cmd *cmd)
{
	_CMD_FIELD_LST *_this = (_CMD_FIELD_LST*)cmd->area;

	/* free resources */
	freeFieldInfo(&_this->finf);
}

int cmd_field_lst_worker(struct _cmd *cmd)
{
	_CMD_FIELD_LST *_this = (_CMD_FIELD_LST*)cmd->area;

	int             rc = 0;
	char            ret_rec[32000];
	int             record_len;
	_CMD            *cmdlist;
	_CMD_FIELD      *field;

	/* setup fields to return */
	setupFieldInfo(&_this->finf, cmd->field);
	if ((rc = sendFieldInfo(&_this->finf)) != 0) return rc;

	cmdlist = cmd_glob.commands;
	while (1)
	{
		if (!cmdlist->name[0]) break;

		if (strcmp(cmdlist->name, _this->funcname) == 0)
		{
			/* requested function found */
			field = cmdlist->field;
			if (field->name[0])
			{
				while (field->name[0])
				{
					/* prepare record data */
					stripStrbuf(_this->f_fldname, sizeof(_this->f_fldname), field->name);
					stripStrbuf(_this->f_fldlname, sizeof(_this->f_fldlname), field->lname);
					_this->f_length = field->size;
					_this->f_fmti[0] = field->fmti;
					_this->f_fmti[1] = 0;
					_this->f_def = field->used;
					stripStrbuf(_this->f_desc, sizeof(_this->f_desc), field->desc);

					/* send a record */
					if ((rc = sendFieldData(&_this->finf, cmd->field)) != 0)
					{
						return rc;
					}

					field++;
				}

				return rc;
			}
			else
			{
				/* function has no field */
				return 16;
			}
		}

		cmdlist = cmdlist + 1;
	}

	return sendErrorInfo(666, cmd->name, "INVALID FUNCTION NAME", _this->funcname);
}


/*-----------------------------------------------------------------*/
/*-----------------------------------------------------------------*/
int b48c_symbol_commands_get(_CMD **scmd);

/* all modules with commands have to put here ---------------------*/
_MCMD   mcmd[] = {
	cmd_commands_get


};
/*-----------------------------------------------------------------*/


/*===================================================================*/
/*                              M A I N                              */
/* ----------------------------------------------------------------- */
/* Function..: The main program                                      */
/* Input.....: Command String                                        */
/* Output....: Function dependent returncode                         */
/*===================================================================*/
int main(int argc, char *argv[])
{
	int        *r1;
	char        *pWQE;
	char        *pURB;
	int          rlen;
	int          alen;
	int          rc = 0;
	char        *pCmd;
	int          lCmd;

	/* set list of module initializer functions to global vars */
	cmd_glob.mcmd = mcmd;
	cmd_glob.mcmd_size = sizeof(mcmd);

	if (isTrace())
	{
		bss_msgl("7510T * B48CMDCL - START ********************************", NULL, 0);

		bss_msgl("7510T API VERSION........: <S>", VID_CMDCL_VERSION, strlen(VID_CMDCL_VERSION));
		bss_msgl("7510T API BUILD..........: <S>", VID_CMDCL_BUILD, strlen(VID_CMDCL_BUILD));
		bss_msgl("7510T API USER...........: <S>", (cmd_glob.user[0]) ? cmd_glob.user : "N/A",
			(cmd_glob.user[0]) ? strlen(cmd_glob.user) : 3);
		bss_msgl("7510T STC USER...........: <S>", cmd_glob.stcuser, strlen(cmd_glob.stcuser));
		bss_msgl("7510T TARGET SSID........: <S>", cmd_glob.target_ssid, strlen(cmd_glob.target_ssid));
		bss_msgl("7510T DATE MASK..........: <S>", cmd_glob.dmsk, strlen(cmd_glob.dmsk));
		bss_msgl("7510T ENCODING...........: <S>", cmd_glob.encoding, strlen(cmd_glob.encoding));
		bss_msgl("7510T TRACE..............: <S>", cmd_glob.trace, strlen(cmd_glob.trace));
		bss_msgl("7510T ---------------------------------------------------", NULL, 0);
	}

	pCmd = argv[1];
	lCmd = strlen(argv[1]);

	/* command processor normally returns 0 (ok), 16 (no data found) or 20 (error info (dbinf)) */
	rc = processCmd(pCmd, lCmd);

	return 0;
}
