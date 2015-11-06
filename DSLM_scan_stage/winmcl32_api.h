//////////////////////////////////////////////////////////////////////////////
// File       : winmcl32_api.h
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//    Global Variables
//////////////////////////////////////////////////////////////////////////////

#ifndef __WINMCL_DLL
#define __WINMCL_DLL

// Responses from API functions (MC_....).
#define WMCL_OPERATION_OK                     0 // General respponse, if no
                                                // error.
#define WMCL_OPERATION_FAILED                 1 // General error response.
#define WMCL_BUSY                             2 // WMCL is busy.

// Error code, stored in ERROR_STRUCT, returned by MC_get_error().

// General error codes.
#define WMCL_INVALID_COMMAND                100 // Invalid command entered by
                                                // API function.

#define WMCL_TIMEOUT                        102 // No response from thread
                                                // function.
#define WMCL_NOT_INITIALISED                103 // MC_init() has not been
                                                // called yet.

#define WMCL_CREATE_EVENT_FAILED            111 // Unable to create Win32
                                                // event.
#define WMCL_REGISTER_EVENT_FAILED         112 // Unable to register event
                                                // with driver
#define WMCL_NOT_CONCURRENT					113 // API function failed to run
												// because of job marking

// Installation / Helper card errors.
#define WMCL_NO_HC3_CARD_AT_ADDRESS         200 // Magic code not read.
#define WMCL_ONLY_ONE_INSTANCE              201 // Only one instance of
                                                // WMCL allowed.
#define WMCL_HC_ACCESS_ERROR                202 // HC/3 access error.
#define WMCL_NO_HCDRV                       203 // Could not open HCDRV.

//WMCL file / memory errors
#define WMCL_GCX_FILE_NOT_FOUND             300 // MCL vector file not found.
#define WMCL_DATA_OVERFLOW                  301 // If data is too high or
                                                // too low.
#define WMCL_WRONG_GCX_FILE_FORMAT          302 // Error while reading
                                                // WMCL file.
#define WMCL_MEMORY_ERROR                   303 // Not enough memory for FIFO.
#define WMCL_FILE_MAPPING_ERROR             304 // Memory mapped file error.
#define WMCL_HC_QUEUE_ERROR                 309 // If download to kernel mode
                                                // queue failed

#define WMCL_CORR_FILE_NOT_FOUND            311 // Correction table file
                                                // not found.
#define WMCL_WRONG_CORR_FILE_FORMAT         312 // Correction table file
                                                // format wrong (LT)
#define WMCL_LASER_PARAMETER_BOUNDS         313 // A parameter value was
                                                // outside the legal bounds.

#define WMCL_POWER_FILE_NOT_FOUND           315 // Power correction table file
                                                // not found.
#define WMCL_WRONG_POWER_FILE_FORMAT        316 // Power table file format
                                                // wrong (PT)

#define WMCL_WRONG_POWER_FILE_CHECKSUM      317 // Power table file format
                                                // wrong power table check
                                                // sum.
#define WMCL_DPL_POWER_OUT_OF_RANGE         318 //

#define WMCL_WRONG_INCLUDE_DATA_FORMAT      319 // INCLUDE_DATA block is
                                                // Missing begin or end magic
                                                // value.
#define WMCL_BAD_INCLUDE_DATA               320 // INCLUDE_DATA block address
                                                // cannot be read.
#define WMCL_BAD_DATA_POINTER               321 // Gcx data block cannot be
                                                // read
#define WMCL_EVENT_RESET_FAILED             322 // Unable to reset win32
                                                // event.
#define WMCL_SYSTEM_ERROR                   323 // System error.

#define WMCL_OUTPUT_QUEUE_ERROR             504 // HC/3 Queue error.
#define WMCL_OUTPUT_FIFO_ERROR              505 // HC/3 Fifo error.
#define WMCL_OUTPUT_FIFOSTART_ERROR         506 // HC/3 Fifo start error.
#define WMCL_OUTPUT_SOFTWARE_ABORT_ERROR    507 // Software abort error.
#define WMCL_OUTPUT_UPCALL_ERROR            508 // HC/3 Fifo upcall error,
                                                // now deprecated
#define WMCL_OUTPUT_UNEXPECTED_F2_ERROR     509 // HC/3 Fifo unexpected F2.

#define WMCL_OUTPUT_UPCALL_FIFO_EMPTY       510
#define WMCL_OUTPUT_UPCALL_FIFO_FULL        511
#define WMCL_OUTPUT_UPCALL_FIFO_FUNC1       512
#define WMCL_OUTPUT_UPCALL_FIFO_HALTED      513
#define WMCL_OUTPUT_UPCALL_FIFO_MARK_ABORT  514 // HC hardware abort error
#define WMCL_OUTPUT_UPCALL_UNEXPECTED_INT_REQ_STATUS 515


// Status codes.
#define WMCL_WAIT_FOR_DO_MARK               700

#define WMCL_INTERNAL_ERROR                 800

// Global Status information: MC_get_status()
// If an error detected, the error code can be checked by calling 
// function MC_get_error().

#define STATUS_IDLE						0x0001
#define STATUS_LOADING_JOB              0x0002
#define STATUS_MARKING					0x0004
#define STATUS_WAITING_FOR_BEGIN		0x0008

// Remaining Constants.

// The error code structure: Code, see #defines above.
// Msg = textual information.
#define ERROR_MSG_LENGTH 255
typedef struct _ERROR_STRUCT
{
    unsigned long Code;
    char Msg[ERROR_MSG_LENGTH];

}ERROR_STRUCT;

// The field distortion correction table structure.
#define GRID_SIDE   65                  // One side of the correction grid.
#define GRID_SIZE   GRID_SIDE * GRID_SIDE   // Grid is 65 by 65 values.

#define COUNTS_PER_GRID 1024                // 65 * 1024 values.

// Field distortion correction table format.
typedef struct _CORRTABLE
{
    long XData[GRID_SIZE];
    long YData[GRID_SIZE];
    long ZData[GRID_SIZE];

} CORRTABLE;

// Power correction table format.
#define POWER_POINTS 256

typedef struct _POWERTABLE
{
    // The actual Port B value.
    unsigned long PowerCorrect[POWER_POINTS];
} POWERTABLE;

// The version info index.
enum WMCLVERINFOINDEX
{
    WMCLVI_DRIVER = 0,
    WMCLVI_DLL,
	WMCLVI_FPGA
};

//////////////////////////////////////////////////////////////////////////////
// LASERPARAMETERSET structure definition
//////////////////////////////////////////////////////////////////////////////	

//The following structure contains all laser marking process data. If 
//a GCX file is processed, the current settings are stored in a list of 
//up to 64 tables of type PSET. 
struct LASERPARAMETERSET
{
	unsigned long BreakAngle;
	unsigned long FPSEnable;
	
	unsigned long Power;
	unsigned long PowerDelay;				// u Secs, currently
	unsigned long QSwitchPeriod;			// u Secs, currently 250 nano Sec 
											// granularity
	unsigned long QSwitchWidth;				// u Secs, currently 250 nano Sec
											// granularity
	unsigned long Intensity;				// units, 0- 0xffff, as a power %
	unsigned long StepPeriod;				// u Secs, currently assumed 10 u 
											// Sec granularity
	unsigned long JumpSize;					// 10 nMeter
	unsigned long JumpDelay;				// u Secs, currently
	unsigned long MarkSize;					// 10 nMeter
	unsigned long PolyLineDelay;				// u Secs
	unsigned long StrokeDelay;				// u Secs
	//unsigned long LaserOnDelay;				// u Secs		// GM - Feb. 2, 04
	long LaserOnDelay;						// u Secs
	unsigned long LaserOffDelay;			// u Secs
	unsigned long DitherWidth;				// dithering is ignored if 0
	unsigned long DitherFeed;				// radius of dither circle
};

//Global Laser Parameter set
typedef LASERPARAMETERSET PSET;

//////////////////////////////////////////////////////////////////////////////
//    GCX record identifiers
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// on file level:

// list begin (4 byte)          long
#define MD_LIST_BEGIN           0x01

// list end (4 byte)            long
#define MD_LIST_END             0x02

// MD_include                   long, include filename must be terminated
//                                    by an MD_INCLUDE_END record.
#define MD_INCLUDE              0x05

// NOTE: INCLUDE text is UNICODE wchar_t, 2 bytes each

// include end (2 byte)         wchar_t, packed to next long boundary
//                                       as necessary
#define MD_INCLUDE_END          0x00

// MD_include_data              long, void * pGCXdata, unsigned long ulsize
//                                    (size in bytes)
#define MD_INCLUDE_DATA         0x06

// comment begin (4 byte)       long, text length variable, but event number 
//                                    of characters; blank must be added, if 
//                                    necessary
#define MD_COMMENT_BEGIN        0x07

// NOTE: COMMENT text is UNICODE wchar_t, 2 bytes each

// comment end (2 byte)         wchar_t, packed to next long boundary
//                                       as necessary
#define MD_COMMENT_END          0x00

//start of parameters block (4 byte)
#define MD_PARAMETER_SET_BEGIN	0x08

//end of parameters block (4 byte)
#define MD_PARAMETER_SET_END	0x09


// select a parameter set (8 byte):  long, long parameter set selector (0...63)
#define MD_SELECT_PARAMETER_SET 0x0A
        
// MD_jump_abs (16 byte):       long, dword xpos, dword xpos, dword zpos
#define MD_JUMP_ABS             0x10

// MD_jump_rel (16 byte):       long, dword xpos, dword xpos, dword zpos
#define MD_JUMP_REL             0x11


// MD_mark_abs (16 byte):       long, dword xpos, dword xpos, dword zpos
#define MD_MARK_ABS             0x12

// MD_mark_rel (16 byte):       long, dword xpos, dword xpos, dword zpos
#define MD_MARK_REL             0x13

// MD_move_abs (16 byte):       long, dword xpos, dword xpos, dword zpos
#define MD_MOVE_ABS             0x14

// MD_move_rel (16 byte):       long, dword xpos, dword xpos, dword zpos
#define MD_MOVE_REL             0x15

// MD_shoot (4 byte):           long (intensity is determined by
//                                   MD_SHOOT_TIME)
#define MD_SHOOT                0x18

// MD_global_transform (16 byte): long, float angleRadians,
//                               float xTranslate, float yTranslate
//                               (rotate, then translate)
#define MD_GLOBAL_TRANSFORM     0x20

// MD_part_transform (16 byte): long, float angleRadians, float xTranslate,
//                              float yTranslate
//                              (translate, then rotate)
#define MD_PART_TRANSFORM       0x21

// MD_object_transform (16 byte):long, float angleRadians,
//                              float xTranslate, float yTranslate
//                              (translate, then rotate)
#define MD_OBJECT_TRANSFORM     0x22

// Alternate form for global transform
// MD_global_matrix (28 byte):  long, float a, float b, float c,
//                              float d, float x0, float y0
#define MD_GLOBAL_MATRIX        0x23

// Alternate form for part transform
// MD_part_matrix (28 byte):    long, float a, float b, float c,
//                              float d, float x0, float y0
#define MD_PART_MATRIX          0x24

// Alternate form for object transform
// MD_object_matrix (28 byte):  long, float a, float b, float c,
//                              float d, float x0, float y0
#define MD_OBJECT_MATRIX        0x25

// Identifies the offset to be applied to the data for the specified
// scan head.
// This will reset the beam dump output mode for the specified head.
// The offset will be scaled through the universal matrix.
// MD_Set_Output_Offset (20 Byte) long, long, long, long, long 
#define MD_SET_OUTPUT_OFFSET    0x26


//MD_set_step_period (8 byte):	long, long period
#define MD_SET_STEP_PERIOD		0x41

//MD_set_mark_size (8 byte):	long, long size
#define MD_SET_MARK_SIZE		0x42

//MD_set_jump_size (8 byte):	long, long size	
#define MD_SET_JUMP_SIZE		0x43

//MD_set_power (8 byte):		long, long power
#define MD_SET_POWER			0x44

//MD_set_intensity (8 byte):	long, long intensity
#define MD_SET_INTENSITY		0x45

//MD_SET_POLYLINE_DELAY (8 byte):	long, long delay time
#define MD_SET_POLYLINE_DELAY	0x46

//MD_set_jump_delay (8 byte):	long, long delay time
#define MD_SET_JUMP_DELAY		0x47

//MD_set_stroke_delay (8):		long, long delay time
#define MD_SET_STROKE_DELAY		0x48

//MD_SET_LASER_ON_DELAY	(8):	long, long delay time
#define MD_SET_LASER_ON_DELAY	0x49

//MD_SET_LASER_OFF_DELAY	(8):	long, long delay time
#define MD_SET_LASER_OFF_DELAY	0x4A

//MD_set_power_delay (8):		long, long delay time	
#define MD_SET_POWER_DELAY		0x4D

//MD_set_FPS_enable (8):		long, long value	
#define MD_SET_FPS_ENABLE		0x60

//MD_set_qswitch_period (8):	long, long period	
#define MD_SET_QSWITCH_PERIOD	0x61

//MD_set_qswitch_width (8):		long, long width
#define MD_SET_QSWITCH_WIDTH	0x62

//MD_set_break_angle (8):		long, long break angle
#define MD_SET_BREAK_ANGLE		0x64

//MD_set_dither_width (8):		long, long dither width
#define MD_SET_DITHER_WIDTH		0x65

//MD_set_dither_Feed (8):		long, long dither width
#define MD_SET_DITHER_FEED		0x66


// MD_repeat(4)
#define MD_REPEAT				0x200

// MD_nrepeat(8):				long, dword times to repeat
#define MD_NREPEAT				0x201

// MD_reset_tracking(4)
#define MD_RESET_TRACKING		0x202

// MD_start_tracking(4)
#define MD_START_TRACKING		0x203

// MD_stop_tracking(4)
#define MD_STOP_TRACKING		0x206

// MD_set_remote_execute (8):	long, dword ON/OFF
#define MD_SET_REMOTE_EXECUTE	0x204

// MD_set_$mark_error (8):		long, dword ON/OFF
#define MD_SET_MARK_ERROR		0x205

// MD_raster_abs( (3+N) * 4)	long, dword [X,Y N] and g(0) - g(N-1)
#define MD_RASTER_ABS		    0x210

// MD_raster_rel( (3+N) * 4)	long, dword [X,Y N] and g(0) - g(N-1)
#define MD_RASTER_REL		    0x211

// MD_WAIT_BEGIN_MARK (4)		long -- GM - Aug 23, 04
#define MD_WAIT_BEGIN_MARK	    0x300

// MD_WAIT_(8)					long, dword microseconds to wait  --GM - Aug 23, 04
#define MD_WAIT				    0x301



// Defines for setting the Raster Mode

#define RASTER_PWM_ONLY 1
#define RASTER_8BIT_ONLY 2

//////////////////////////////////////////////////////////////////////////////
// WinMCL32 API Functions
//////////////////////////////////////////////////////////////////////////////

// This is for clients who load winmcl32 Explicitly, and define pointers
// to the API functions.
#ifndef EXPLICIT_WINMCL32

#ifdef __cplusplus
extern "C"
{
#endif

// Define on compiler command line (or VisualStudio project settings) if
// needed.
#ifdef WINMCL32_EXPORT
    // Export WinMCL32.DLL functions.
    #define WINMCL32_SPEC __declspec( dllexport )
#else
    // Assume applications need to import WinMCL32.DLL functions.
    #define WINMCL32_SPEC __declspec( dllimport )
#endif

////////////////////////////////////////////////////////////////////////
//  MC_init
//
//	Routine Description:
//		Initializes the gStreamDriver and gWmcl objects.
//
//	Parameters:
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_init(void);

////////////////////////////////////////////////////////////////////////
//  MC_exit
//
//	Routine Description:
//		Performs actions required on exit from the dll.
//
//	Parameters:
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_exit(void);

////////////////////////////////////////////////////////////////////////
//  MC_reset
//
//	Routine Description:
//		Initializes the system if it has not been initialized,
//		otherwize performs reset actions.
//
//	Parameters:
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_reset(void);

////////////////////////////////////////////////////////////////////////
//  MC_get_version
//
//	Routine Description:
//		Get the vesion information strings.
//
//	Parameters:
//		Version - Pointer to a buffer to receive the version string
//		    This is assumed to be at least 256 bytes long.
//		Part - Version index for the required information:
//		    0 = Driver.
//			1 = DLL.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall __stdcall MC_get_version(
                                                char *Version,
                                                const unsigned long Part);

////////////////////////////////////////////////////////////////////////
//  MC_get_error
//
//	Routine Description:
//		Get the error code and message.
//		This command is only useful after a previous command has
//		returned the WMCL_OPERATION_FAILED status.
//
//	Parameters:
//		pErrorStruct - Pointer to a structure that will received
//		    the error code and message.
//
//	Return Value:
//		WMCL_OPERATION_OK.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_error(
                                        ERROR_STRUCT* pErrorStruct);

////////////////////////////////////////////////////////////////////////
//  MC_set_timeout
//
//	Routine Description:
//		Specifies how long WinMCL32 should wait for a response from HCDRV.
//		The default value (after MC_init or MC_reset )is 10 seconds,
//		which is more than adequate in all normal circumstances.
//		You may need to increase this value if you are using a very long 
//		StepPeriods (roughly, more than 5 milliseconds, although this figure 
//		is highly dependent upon the exact mixture of vectors produced by your
//		application).
//
//	Parameters:
//		NewTime - the desired timeout value in milliseconds
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_timeout(
                                        const unsigned long NewTime);

////////////////////////////////////////////////////////////////////////
//  MC_get_timeout
//
//	Routine Description:
//		Get the current timeout value. (in milliseconds)
//
//	Parameters:
//		None
//
//	Return Value:
//		NOT the status of the operation!
//		Instead: 0 if an error occurred, otherwise the current
//		timeout value.
//
//	Comments:
//		If an error has occurred, you can use MC_get_error as
//		usual to retrieve the error code.
//
WINMCL32_SPEC unsigned long __stdcall MC_get_timeout( void );

////////////////////////////////////////////////////////////////////////
//  MC_get_num_cards
//
//	Routine Description:
//		Get the number of helper cards detected by the kernal mode
//		driver.
//
//	Parameters:
//		pNumCards: pointer to a variable that receives the
//		    number of cards.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_num_cards(
                                        unsigned long* pnCards);

////////////////////////////////////////////////////////////////////////
//  MC_open_vector_dump_file
//
//	Routine Description:
//		Opens the file that will record the data that is sent
//		to the driver.
//
//	Parameters:
//		pszFileName - Pointer to the name of the vector
//		    dump file to open.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_open_vector_dump_file(
                                        const char* pszFileName);

////////////////////////////////////////////////////////////////////////
//  MC_close_vector_dump_file
//
//	Routine Description:
//		Closes the file that recorded the data that was sent
//		to the driver.
//
//	Parameters:
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_close_vector_dump_file(void);

////////////////////////////////////////////////////////////////////////
//  MC_load_job
//
//	Routine Description:
//		Opens a GCX Data File on disk and places it in the Job
//		Queue for subsequent processing.
//
//	Parameters:
//		jobfile - Pointer to the GCX file name.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_load_job(const char *jobfile);

////////////////////////////////////////////////////////////////////////
//  MC_load_job_from_memory
//
//	Routine Description:
//		Opens a GCX Data File in application memory and places it
//		in the Job Queue for subsequent processing.
//
//	Parameters:
//		startAddress - Pointer to the start of the job file in
//		    application memory.
//		length - Length of the job file (in bytes).
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_load_job_from_memory(
                            char *startAddress, const unsigned long length);


////////////////////////////////////////////////////////////////////////
//  MC_start_mark
//
//	Routine Description:
//		Starts the marking thread.
//
//	Parameters:
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_start_mark(void);

////////////////////////////////////////////////////////////////////////
//  MC_start_mark_on_begin
//
//	Routine Description:
//		Initializes vector processing, and begins vector processing
//		and output.
//		Output will start when the external "$START_MARK" signal
//		is asserted on the 9-pin Sub-D connector.
//
//	Parameters:
//		TimeOut - Maximum time, in milliseconds, that the program
//		    will wait for the "$START_MARK" signal.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_start_mark_on_begin(
                                                const unsigned long TimeOut);

////////////////////////////////////////////////////////////////////////
//  MC_abort_mark
//
//	Routine Description:
//		Aborts the currently executing marking job.
//
//	Parameters:
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//		This command leaves all laser signals in an undefined state.
//
WINMCL32_SPEC unsigned long __stdcall MC_abort_mark(void);

////////////////////////////////////////////////////////////////////////
//  MC_get_status
//
//	Routine Description:
//		Get the system status.
//		The system status value consists of two groups of bits.
//		The first cumulatively indicates the progress of a job
//		through successive stages of processing. The second
//		indicates error conditions.
//		The bits are defined by the STATUS defines.
//
//	Parameters:
//		Status - Pointer to a variable that receives the current
//		    system status code.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_status(unsigned long* Status);

////////////////////////////////////////////////////////////////////////
//  MC_get_cur_xyz
//
//	Routine Description:
//		Return the current X, Y, and Z output position for the
//		selected Helper Card.
//		The returned position has had Field Distortion Correction
//		applied to it, and does not necessarily match any
//		particular position in the input GCX Data File.
//
//	Parameters:
//		Index - Helper Card number.
//		XPosition, etc. - Pointers to variables that receive the
//		    values.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_cur_xyz(unsigned short Index,
                                                     long* XPosition,
                                                     long* YPosition,
                                                     long* ZPosition);

////////////////////////////////////////////////////////////////////////
//  MC_jump_abs
//
//	Routine Description:
//		Performs a controlled JUMP ABS to the given location,
//		using the current laser parameter set.
//
//	Parameters:
//		X, Y, Z - Location coordinates.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_jump_abs(long X, long Y, long Z);

////////////////////////////////////////////////////////////////////////
//  MC_jump_rel
//
//	Routine Description:
//		Performs a controlled JUMP REL to the given location,
//		using the current laser parameter set.
//
//	Parameters:
//		X, Y, Z - Location coordinates.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_jump_rel(long X, long Y, long Z);

////////////////////////////////////////////////////////////////////////
//  MC_shoot
//
//	Routine Description:
//		Performs a SHOOT, using the current laser parameter set.
//
//	Parameters:
//		X, Y, Z - Location coordinates.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_shoot(unsigned long ShootTime);

////////////////////////////////////////////////////////////////////////
//  MC_get_head_status
//
//	Routine Description:
//		Returns the head status for the master Helper Card.
//
//	Parameters:
//		IndexCard - card Index
//		Status - Content of the Helper Card head status register.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_head_status(unsigned short IndexCard,
                                                unsigned short * Status);

////////////////////////////////////////////////////////////////////////
//  MC_exit_mark
//
//	Routine Description:
//		Gracefully exit from any repeat or nrepeat loop.
//
//	Parameters:
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_exit_mark(void);

////////////////////////////////////////////////////////////////////////
//  MC_set_raster_mode
//
//	Routine Description:
//		Set what laser control output should be modulated along a raster
//		line.
//
//	Parameters:
//		RasterMode - which laser output to use along a raster line. 
//			RASTER_8BIT_ONLY, RASTER_PWM_ONLY, or any other value means both
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_raster_mode(unsigned long RasterMode);

////////////////////////////////////////////////////////////////////////
//  MC_get_begin_mark
//
//	Routine Description:
//		Returns the status of the external "$BEGIN_MARK" signal on
//		the master Helper card.
//
//	Parameters:
//		Status - Pointer to variable that receives the current
//			signal status (1= ASSERTED, 0=INACTIVE).
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_begin_mark(
                                                unsigned short *Status);

////////////////////////////////////////////////////////////////////////
//  MC_get_mark_abort
//
//	Routine Description:
//		Returns the status of the external "MARK_ABORT" signal on
//		the master Helper card.
//
//	Parameters:
//		Status - Pointer to variable that receives the current
//			signal status (1= ASSERTED, 0=INACTIVE).
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_mark_abort(
                                                unsigned short *Status);

////////////////////////////////////////////////////////////////////////
//  MC_get_optional_status
//
//	Routine Description:
//		Returns the status of the external OPT2 signal on
//		the master Helper card.
//
//	Parameters:
//		Status - Pointer to variable that receives the current
//			signal status (1= ASSERTED, 0=INACTIVE).
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_optional_status(
                                                unsigned short *Status);

////////////////////////////////////////////////////////////////////////
//  MC_set_remote_execute
//
//	Routine Description:
//		Set the external "$REMOVE_EXECUTE" signal at all Helper
//		Cards.
//
//	Parameters:
//		Statue - The required signal state (1= ASSERTED, 0=INACTIVE).
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_remote_execute(
                                          const unsigned short State);

////////////////////////////////////////////////////////////////////////
//  MC_set_mark_error
//
//	Routine Description:
//		Set the external "MARK_ERROR" signal at all Helper
//		Cards.
//
//	Parameters:
//		Statue - The required signal state (1= ASSERTED, 0=INACTIVE).
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_mark_error(
                                          const unsigned short State);

////////////////////////////////////////////////////////////////////////
//  MC_get_portA_input
//
//	Routine Description:
//		Gets the current state of the Port A input register on
//		a given Helper Card. The command can only be issued
//		when WinMCL32 is idle.
//
//	Parameters:
//		Index - Helper Card number.
//		Setting - Pointer to a buffer that receives the current
//		          state of Port A. Note that the current hardware
//		          implementation of Port A is 8 bits wide.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_portA_input(
                                          unsigned short Index,
                                          long* Setting);

////////////////////////////////////////////////////////////////////////
//  MC_set_corrtable
//
//	Routine Description:
//		Loads the Field-Distortion Correction Table for the
//		selected Helper Card from the given file.
//
//	Parameters:
//		Index - Helper Card number.
//		FileName - Field-distortion correction table file name.
//
//	Return Value:
//		WMCL_OPERATION_OK, WMCL_OPERATION_FAILED.
//
//	Comments:
//		The table (X,Y,Z) must be contained in FileName,
//		a file containing 3 * 65*65 words (16bit).
//
WINMCL32_SPEC unsigned long __stdcall MC_set_corrtable(unsigned short Index,
                                         char* FileName);

////////////////////////////////////////////////////////////////////////
//  MC_set_corrtableFromMemory
//
//	Routine Description:
//		Copies correction table values to the indexed correction table
//		from memory.
//
//	Parameters:
//		nDestIndex - Card index of the destination correction table.
//		pSourceCorrectionTable - Address of the source correction table.
//
//	Return Value:
//		WMCL_OPERATION_OK, WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_corrtableFromMemory(
                                        unsigned short wDestIndex,
										CORRTABLE *pSourceCorrectionTable);

////////////////////////////////////////////////////////////////////////
//  MC_reset_corrtable
//
//	Routine Description:
//		Resets the Field-Distortion Correction Table for the
//		selected Helper Card to the default values
//		(i.e. no correction).
//
//	Parameters:
//		Index - Helper Card number.
//
//	Return Value:
//		WMCL_OPERATION_OK, WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_reset_corrtable(unsigned short Index);

////////////////////////////////////////////////////////////////////////
//  MC_get_corrtable
//
//	Routine Description:
//		Returns a pointer to the field-distortion correction table
//		for the selected Helper Card.
//
//	Parameters:
//		wSourceIndex - Card index of the source correction table.
//		pDestCorrectionTable - Address of the destination correction table.
//
//	Return Value:
//		WMCL_OPERATION_OK, WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_corrtable(
                                         unsigned short wSourceIndex,
									     CORRTABLE *pDestCorrectionTable);

////////////////////////////////////////////////////////////////////////
//  MC_set_powertable
//
//	Routine Description:
//		Loads the Laser Power Calibration Table for the selected
//		Helper Card from the given file.
//
//	Parameters:
//		Index - Helper Card number.
//		Pointer - Pointer to power calibration table file name.
//
//	Return Value:
//		WMCL_OPERATION_OK, WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_powertable(
                                          unsigned short Index,
                                          char* FileName);

////////////////////////////////////////////////////////////////////////
//  MC_set_powertableFromMemory
//
//	Routine Description:
//		Copies power table values to the indexed correction table
//		from memory.
//
//	Parameters:
//		nDestIndex - Card index of the destination power table.
//		pSourceCorrectionTable - Address of the source power table.
//
//	Return Value:
//		WMCL_OPERATION_OK, WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_powertableFromMemory(
                                        unsigned short wDestIndex,
										POWERTABLE *pSourcePowerTable);

////////////////////////////////////////////////////////////////////////
//  MC_reset_powertable
//
//	Routine Description:
//		Resets the Laser Power Calibration Table for the selected
//		Helper Card to the default values (i.e. a 1:1 power mapping).
//
//	Parameters:
//		Index - Helper Card number.
//
//	Return Value:
//		WMCL_OPERATION_OK, WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_reset_powertable(unsigned short Index);

////////////////////////////////////////////////////////////////////////
//  MC_get_powertable
//
//	Routine Description:
//		Returns a pointer to the Laser Power Calibration Table for
//		the selected Helper Card.
//
//	Parameters:
//		wSourceIndex - Card index of the source power table.
//		pDestPowerTable - Address of the destination power table.
//
//	Return Value:
//		WMCL_OPERATION_OK, WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_powertable(
                                          unsigned short wSourceIndex,
                                          POWERTABLE *pDestPowerTable);

////////////////////////////////////////////////////////////////////////
//  MC_set_xy_exchange
//
//	Routine Description:
//		Set the x-y exchange flag.
//		If TRUE, the X and Y output channels are swapped.
//		This is independent of the Transform Matrix.
//
//	Parameters:
//		Value - Desired flag state.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_xy_exchange(
                                                const unsigned short Value);

////////////////////////////////////////////////////////////////////////
//  MC_get_xy_exchange
//
//	Routine Description:
//		Returns the current x-y exchange flag value.
//
//	Parameters:
//		Value - Pointer to variable that receives the current
//		    flag state.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_xy_exchange(
                                                unsigned short * Value);

////////////////////////////////////////////////////////////////////////
//  MC_set_x_flip
//
//	Routine Description:
//		Set the x flip flag.
//		If TRUE, the outut X-axis will be inverted.
//		This is independent of the Transform Matrix.
//
//	Parameters:
//		Value - Desired flag state.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_x_flip(
                                                const unsigned short Value);

////////////////////////////////////////////////////////////////////////
//  MC_get_x_flip
//
//	Routine Description:
//		Returns the current x-flip flag value.
//
//	Parameters:
//		Value - Pointer to variable that receives the current flag
//		    state.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_x_flip(
                                                unsigned short * Value);

////////////////////////////////////////////////////////////////////////
//  MC_set_y_flip
//
//	Routine Description:
//		Set the y flip flag.
//		If TRUE, the outut Y-axis will be inverted.
//		This is independent of the Transform Matrix.
//
//	Parameters:
//		Value - Desired flag state.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_y_flip(
                                                const unsigned short Value);

////////////////////////////////////////////////////////////////////////
//  MC_get_y_flip
//
//	Routine Description:
//		Returns the current y-flip flag value.
//
//	Parameters:
//		Value - Pointer to variable that receives the current flag
//		    state.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_y_flip(
                                                unsigned short *Value);

////////////////////////////////////////////////////////////////////////
//  MC_set_xform_matrix
//
//	Routine Description:
//		Set the transform matrix for the Universal Matrix.
//		The transform matrix is applied to all incoming vectors
//		to provide scaling, rotation, and other transformations
//		of the vector ordinates before field-distortion correction
//		is applied.
//
//	Parameters:
//		a, b, c, d, x0, y0 - Transform matrix coefficient values.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_xform_matrix(
                                const float a, const float b,
                                const float c, const float d,
                                const float x0, const float y0);

////////////////////////////////////////////////////////////////////////
//  MC_get_xform_matrix
//
//	Routine Description:
//		Get the current transform matrix coefficients for the
//		Universal Matrix.
//
//	Parameters:
//		pa, pb, pc, pd, px0, py0 - Pointers to variables to
//		    receive transform matrix parameters.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_xform_matrix(
                                float *pa, float *pb,
                                float *pc, float *pd,
                                float *px0, float *py0);

////////////////////////////////////////////////////////////////////////
//  MC_set_fps_delay
//
//	Routine Description:
//		Set the first pulse suppression Delay value.
//      This represents the time that should elapse between the FPS 
//      Trigger Pulse and the start of Laser Modulation.
//
//	Parameters:
//		FPSDelay - FPS delay in milliseconds.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//		The WinMCL reference document has period defined as milliseconds
//      However, in the actual code, this value is only used in direct
//      comparison to variables declared as microseconds.
//      Therefore, we will define this as microseconds as well.
//      with the same boundary checking as defined in the document (none)
//
WINMCL32_SPEC unsigned long __stdcall MC_set_fps_delay(
                                            const unsigned long FPSDelay );

////////////////////////////////////////////////////////////////////////
//  MC_get_fps_delay
//
//	Routine Description:
//		Return the current first pulse suppression Delay value. 
//
//	Parameters:
//		FPSDelay - pointer to a buffer to contain the current
//		    FPS Delay Value
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//		The WinMCL reference document has period defined as milliseconds
//      However, in the actual code, this value is only used in direct
//      comparison to variables declared as microseconds.
//      Therefore, we will define this as microseconds as well.
//      with the same boundary checking as defined in the document (none)
//
WINMCL32_SPEC unsigned long __stdcall MC_get_fps_delay(
                                            unsigned long* FPSDelay);

////////////////////////////////////////////////////////////////////////
//  MC_select_parameter_set
//
//	Routine Description:
//		Select a laser parameter set for MC_jump_abs, MC_jump_rel
//		and MC_shoot functions.
//
//	Parameters:
//		Index - Parameter set index.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_select_parameter_set(long Index);

////////////////////////////////////////////////////////////////////////
//  MC_set_ParamSet
//
//	Routine Description:
//		Set the global DLL Parameter set at Params[Index] to the
//		values stored in *p
//
//	Parameters:
//		Index - Parameter set index.
//		*p	  - Pointer to the parameters to set.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_ParamSet(int Index, PSET *p);

////////////////////////////////////////////////////////////////////////
//  MC_get_ParamSet
//
//	Routine Description:
//		Get the global DLL Parameter set at Params[Index] and return it in p
//
//	Parameters:
//		Index - Parameter set index.
//		*p	  - Pointer to the parameters to set.
//
//	Return Value:
//		A WMCL errorcode.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_ParamSet(int Index, PSET *p);

////////////////////////////////////////////////////////////////////////
//  MC_reset_ParamSet
//
//	Routine Description:
//		Set the global DLL Parameter set at Params[Index] to the
//		default values
//
//	Parameters:
//		Index - Parameter set index.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_reset_ParamSet(int Index);

////////////////////////////////////////////////////////////////////////
//  MC_set_target_velocity
//
//	Routine Description:
//		Select the target X and Y velocities.
//
//	Parameters:
//		XVelocity - Target X Velocity.
//		YVelocity - Target Y Velocity.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_target_velocity(
                                    float XVelocity, float YVelocity);

////////////////////////////////////////////////////////////////////////
//  MC_get_target_velocity
//
//	Routine Description:
//		Get the target X and Y velocities, that were previously
//		set in MC_set_target_velocity.
//
//	Parameters:
//		pXVelocity - Pointer to variable to receive the
//					 Target X Velocity.
//		pYVelocity - Pointer to variable to receive the
//					 Target Y Velocity.
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_target_velocity(
                                    float *pXVelocity, float *pYVelocity);

////////////////////////////////////////////////////////////////////////
//  MC_reset_tracking
//
//	Routine Description:
//		Reset the tracking variables.
//
//	Parameters:
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_reset_tracking(void);

////////////////////////////////////////////////////////////////////////
//  MC_start_tracking
//
//	Routine Description:
//		Start the tracking adjustments to an object mark.
//
//	Parameters:
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_start_tracking(void);

////////////////////////////////////////////////////////////////////////
//  MC_stop_tracking
//
//	Routine Description:
//		Stops the tracking adjustments to an object mark.
//
//	Parameters:
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_stop_tracking(void);

//////////////////////////////////////////////////////////////////////////////
//  MC_WriteConfigSpaceULong
//
//		Write to the PCI Configuration space of the HC/3 Card
//
//	Parameters:
//		Card - Helper card id
//		Port - Register offset of the PCI Config space to write
//		Data - Data to write to the register
//
//	Return Value:
//		A Wmcl ErrorCode
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_WriteConfigSpaceULong(unsigned long Card,
													unsigned long Port,
													unsigned long Data);

//////////////////////////////////////////////////////////////////////////////
//  MC_ReadConfigSpaceULong
//
//		Reads the PCI Configuration space of the HC/3 Card
//
//	Parameters:
//		Card - Helper card id
//		Port - Register offset of the PCI Config space to write
//		Data - Data to write to the register
//
//	Return Value:
//		A WMCL ErrorCode 
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_ReadConfigSpaceULong(unsigned long Card,
													unsigned long Port,
													unsigned long *pData);




////////////////////////////////////////////////////////////////////////
//  MC_get_job_count
//
//	Routine Description:
//		Returns number of GCX Data Files loaded in the Queue
//		for subsequent processing.
//
//	Parameters:
//		jobfile - Pointer to an unsigned int, that returns the number of
//		the GCX files in the queue
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_get_job_count(unsigned int *pNcount);


////////////////////////////////////////////////////////////////////////
//  MC_reset_job_queue
//
//	Routine Description:
//		Resets the job queue
//
//	Parameters:
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_reset_job_queue();


////////////////////////////////////////////////////////////////////////
//  MC_start_mark_non_blocking
//
//	Routine Description:
//		Starts an independent marking thread.  Returns almost immediately
//      without blocking the caller
//
//	Parameters:
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_start_mark_non_blocking();


////////////////////////////////////////////////////////////////////////
//  MC_start_mark_on_begin_non_blocking
//
//	Routine Description:
//		Starts an independent marking thread.  Returns almost immediately
//      without blocking the caller.  Useful for languages like LabVIEW that
//		have difficulty spawning their own threads.
//      Initializes vector processing, and begins vector processing
//		and output.
//		Output will start when the external "$START_MARK" signal
//		is asserted on the 9-pin Sub-D connector.
//
//	Parameters:
//		TimeOut - Maximum time, in milliseconds, that the program
//		    will wait for the "$START_MARK" signal.
//	Parameters:
//
//	Return Value:
//		WMCL_OPERATION_OK or WMCL_OPERATION_FAILED.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_start_mark_on_begin_non_blocking( unsigned long );



////////////////////////////////////////////////////////////////////////
//  MC_set_external_signal
//
//	Routine Description:
//		Set the external signal pin 50 on the header
//		It's available only in Separate signals modce
//
//	Parameters:
//		Statue - The required signal state (1= ASSERTED, 0=INACTIVE).
//
//	Return Value:
//		WMCL_OPERATION_OK, WMCL_OPERATION_FAILED, WMCL_NOT_CONCURRENT.
//
//	Comments:
//
WINMCL32_SPEC unsigned long __stdcall MC_set_external_signal(
                                          const unsigned short State);




#ifdef __cplusplus
}
#endif

#endif

#endif
////////////////////////////////////////////////////////////////////////
//    end of file
////////////////////////////////////////////////////////////////////////
