/******************************************************************************
 *                                                                         
 *               Agilent Technologies
 *               All rights reserved.
 *
 *****************************************************************************/

#ifndef __AG33250_HEADER
#define __AG33250_HEADER

#include <IviVisaType.h>
#include <unknwn.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

/**************************************************************************** 
 *---------------------------- Attribute Defines ---------------------------* 
 ****************************************************************************/
#ifndef IVI_ATTR_BASE
#define IVI_ATTR_BASE                 1000000
#endif

#ifndef IVI_INHERENT_ATTR_BASE		        
#define IVI_INHERENT_ATTR_BASE		  (IVI_ATTR_BASE +  50000)   /* base for inherent capability attributes */
#endif

#ifndef IVI_CLASS_ATTR_BASE           
#define IVI_CLASS_ATTR_BASE           (IVI_ATTR_BASE + 250000)   /* base for IVI-defined class attributes */
#endif

#ifndef IVI_LXISYNC_ATTR_BASE         
#define IVI_LXISYNC_ATTR_BASE         (IVI_ATTR_BASE + 950000)   /* base for IviLxiSync attributes */
#endif

#ifndef IVI_SPECIFIC_ATTR_BASE        
#define IVI_SPECIFIC_ATTR_BASE        (IVI_ATTR_BASE + 150000)   /* base for attributes of specific drivers */
#endif


/*===== IVI Inherent Instrument Attributes ==============================*/    

    /*- Driver Identification */
#define	AG33250_ATTR_SPECIFIC_DRIVER_DESCRIPTION                  (IVI_INHERENT_ATTR_BASE + 514L)  /* ViString, read-only */
#define	AG33250_ATTR_SPECIFIC_DRIVER_PREFIX                       (IVI_INHERENT_ATTR_BASE + 302L)  /* ViString, read-only */
#define	AG33250_ATTR_SPECIFIC_DRIVER_VENDOR                       (IVI_INHERENT_ATTR_BASE + 513L)  /* ViString, read-only */
#define	AG33250_ATTR_SPECIFIC_DRIVER_REVISION                     (IVI_INHERENT_ATTR_BASE + 551L)  /* ViString, read-only */
#define	AG33250_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION     (IVI_INHERENT_ATTR_BASE + 515L)  /* ViInt32, read-only */
#define	AG33250_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION     (IVI_INHERENT_ATTR_BASE + 516L)  /* ViInt32, read-only */

    /*- Advanced Session Information */
#define	AG33250_ATTR_LOGICAL_NAME                       (IVI_INHERENT_ATTR_BASE + 305L)  /* ViString, read-only */
#define	AG33250_ATTR_IO_RESOURCE_DESCRIPTOR             (IVI_INHERENT_ATTR_BASE + 304L)  /* ViString, read-only */
#define	AG33250_ATTR_DRIVER_SETUP                       (IVI_INHERENT_ATTR_BASE + 7L)    /* ViString, read-only */

    /*- User Options */
#define	AG33250_ATTR_CACHE                              (IVI_INHERENT_ATTR_BASE + 4L)   /* ViBoolean, read-write */
#define	AG33250_ATTR_INTERCHANGE_CHECK                  (IVI_INHERENT_ATTR_BASE + 21L)  /* ViBoolean, read-write */
#define	AG33250_ATTR_QUERY_INSTRUMENT_STATUS            (IVI_INHERENT_ATTR_BASE + 3L)   /* ViBoolean, read-write */
#define	AG33250_ATTR_RANGE_CHECK                        (IVI_INHERENT_ATTR_BASE + 2L)   /* ViBoolean, read-write */
#define	AG33250_ATTR_RECORD_COERCIONS                   (IVI_INHERENT_ATTR_BASE + 6L)   /* ViBoolean, read-write */
#define	AG33250_ATTR_SIMULATE                           (IVI_INHERENT_ATTR_BASE + 5L)   /* ViBoolean, read-write */

    /*- Instrument Identification */
#define	AG33250_ATTR_INSTRUMENT_MANUFACTURER            (IVI_INHERENT_ATTR_BASE + 511L)  /* ViString, read-only */
#define	AG33250_ATTR_INSTRUMENT_MODEL                   (IVI_INHERENT_ATTR_BASE + 512L)  /* ViString, read-only */
#define	AG33250_ATTR_INSTRUMENT_FIRMWARE_REVISION       (IVI_INHERENT_ATTR_BASE + 510L)  /* ViString, read-only */

    /*- Driver Capabilities */
#define	AG33250_ATTR_SUPPORTED_INSTRUMENT_MODELS        (IVI_INHERENT_ATTR_BASE + 327L)  /* ViString, read-only */
#define	AG33250_ATTR_GROUP_CAPABILITIES                 (IVI_INHERENT_ATTR_BASE + 401L)  /* ViString, read-only */


/*===== Instrument-Specific Attributes =====================================*/

    /*- Arbitrary */
#define	AG33250_ATTR_ARB_GAIN                           (IVI_CLASS_ATTR_BASE + 202L)  /* ViReal64, read-write */
#define	AG33250_ATTR_ARB_OFFSET                         (IVI_CLASS_ATTR_BASE + 203L)  /* ViReal64, read-write */
#define	AG33250_ATTR_ARB_SAMPLE_RATE                    (IVI_CLASS_ATTR_BASE + 204L)  /* ViReal64, read-write */

    /*- Waveform */
#define	AG33250_ATTR_ARB_WAVEFORM_HANDLE                (IVI_CLASS_ATTR_BASE + 201L)  /* ViInt32, read-write */
#define	AG33250_ATTR_ARB_FREQUENCY                      (IVI_CLASS_ATTR_BASE + 209L)  /* ViReal64, read-write */
#define	AG33250_ATTR_MAX_NUM_WAVEFORMS                  (IVI_CLASS_ATTR_BASE + 205L)  /* ViInt32, read-only */
#define	AG33250_ATTR_WAVEFORM_QUANTUM                   (IVI_CLASS_ATTR_BASE + 206L)  /* ViInt32, read-only */
#define	AG33250_ATTR_MAX_WAVEFORM_SIZE                  (IVI_CLASS_ATTR_BASE + 208L)  /* ViInt32, read-only */
#define	AG33250_ATTR_MIN_WAVEFORM_SIZE                  (IVI_CLASS_ATTR_BASE + 207L)  /* ViInt32, read-only */

    /*- Output */
#define	AG33250_ATTR_OUTPUT_ENABLED                     (IVI_CLASS_ATTR_BASE + 3L)       /* ViBoolean, read-write */
#define	AG33250_ATTR_OUTPUT_IMPEDANCE                   (IVI_CLASS_ATTR_BASE + 4L)       /* ViReal64, read-write */
#define	AG33250_ATTR_OUTPUT_MODE                        (IVI_CLASS_ATTR_BASE + 1L)       /* ViInt32, read-write */
#define	AG33250_ATTR_OPERATION_MODE                     (IVI_CLASS_ATTR_BASE + 5L)       /* ViInt32, read-write */
#define	AG33250_ATTR_REF_CLOCK_SOURCE                   (IVI_CLASS_ATTR_BASE + 2L)       /* ViInt32, read-write */
#define	AG33250_ATTR_CHANNEL_COUNT                      (IVI_INHERENT_ATTR_BASE + 203L)  /* ViInt32, read-only */
#define	AG33250_ATTR_OUTPUT_FREQUENCY                   (IVI_SPECIFIC_ATTR_BASE + 62L)   /* ViReal64, read-write */
#define	AG33250_ATTR_OUTPUT_FREQUENCY_MAX               (IVI_SPECIFIC_ATTR_BASE + 63L)   /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_FREQUENCY_MIN               (IVI_SPECIFIC_ATTR_BASE + 64L)   /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_FUNCTION                    (IVI_SPECIFIC_ATTR_BASE + 65L)   /* ViInt32, read-write */
#define	AG33250_ATTR_OUTPUT_LOAD                        (IVI_SPECIFIC_ATTR_BASE + 66L)   /* ViReal64, read-write */
#define	AG33250_ATTR_OUTPUT_LOAD_MAX                    (IVI_SPECIFIC_ATTR_BASE + 67L)   /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_LOAD_MIN                    (IVI_SPECIFIC_ATTR_BASE + 68L)   /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_POLARITY                    (IVI_SPECIFIC_ATTR_BASE + 69L)   /* ViInt32, read-write */
#define	AG33250_ATTR_OUTPUT_RAMP_SYMMETRY               (IVI_SPECIFIC_ATTR_BASE + 70L)   /* ViReal64, read-write */
#define	AG33250_ATTR_OUTPUT_RAMP_SYMMETRY_MAX           (IVI_SPECIFIC_ATTR_BASE + 71L)   /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_RAMP_SYMMETRY_MIN           (IVI_SPECIFIC_ATTR_BASE + 72L)   /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_SQUARE_DUTY_CYCLE           (IVI_SPECIFIC_ATTR_BASE + 73L)   /* ViReal64, read-write */
#define	AG33250_ATTR_OUTPUT_SQUARE_DUTY_CYCLE_MAX       (IVI_SPECIFIC_ATTR_BASE + 74L)   /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_SQUARE_DUTY_CYCLE_MIN       (IVI_SPECIFIC_ATTR_BASE + 75L)   /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_STATE                       (IVI_SPECIFIC_ATTR_BASE + 76L)   /* ViBoolean, read-write */
#define	AG33250_ATTR_OUTPUT_SYNC                        (IVI_SPECIFIC_ATTR_BASE + 77L)   /* ViBoolean, read-write */

    /*- Voltage */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_AMPLITUDE           (IVI_SPECIFIC_ATTR_BASE + 78L)  /* ViReal64, read-write */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_AMPLITUDE_MAX       (IVI_SPECIFIC_ATTR_BASE + 79L)  /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_AMPLITUDE_MIN       (IVI_SPECIFIC_ATTR_BASE + 80L)  /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_HIGH                (IVI_SPECIFIC_ATTR_BASE + 81L)  /* ViReal64, read-write */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_HIGH_MAX            (IVI_SPECIFIC_ATTR_BASE + 82L)  /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_HIGH_MIN            (IVI_SPECIFIC_ATTR_BASE + 83L)  /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_LOW                 (IVI_SPECIFIC_ATTR_BASE + 84L)  /* ViReal64, read-write */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_LOW_MAX             (IVI_SPECIFIC_ATTR_BASE + 85L)  /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_LOW_MIN             (IVI_SPECIFIC_ATTR_BASE + 86L)  /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_OFFSET              (IVI_SPECIFIC_ATTR_BASE + 87L)  /* ViReal64, read-write */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_OFFSET_MAX          (IVI_SPECIFIC_ATTR_BASE + 88L)  /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_OFFSET_MIN          (IVI_SPECIFIC_ATTR_BASE + 89L)  /* ViReal64, read-only */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_RANGE_AUTO          (IVI_SPECIFIC_ATTR_BASE + 90L)  /* ViInt32, read-write */
#define	AG33250_ATTR_OUTPUT_VOLTAGE_UNITS               (IVI_SPECIFIC_ATTR_BASE + 91L)  /* ViInt32, read-write */

    /*- Trigger */
#define	AG33250_ATTR_BURST_COUNT                        (IVI_CLASS_ATTR_BASE + 350L)    /* ViInt32, read-write */
#define	AG33250_ATTR_INTERNAL_TRIGGER_RATE              (IVI_CLASS_ATTR_BASE + 310L)    /* ViReal64, read-write */
#define	AG33250_ATTR_TRIGGER_SOURCE                     (IVI_CLASS_ATTR_BASE + 302L)    /* ViInt32, read-write */
#define	AG33250_ATTR_TRIGGER_DELAY                      (IVI_SPECIFIC_ATTR_BASE + 32L)  /* ViReal64, read-write */
#define	AG33250_ATTR_TRIGGER_DELAY_MAX                  (IVI_SPECIFIC_ATTR_BASE + 33L)  /* ViReal64, read-only */
#define	AG33250_ATTR_TRIGGER_DELAY_MIN                  (IVI_SPECIFIC_ATTR_BASE + 34L)  /* ViReal64, read-only */
#define	AG33250_ATTR_TRIGGER_SLOPE                      (IVI_SPECIFIC_ATTR_BASE + 35L)  /* ViInt32, read-write */

    /*- StandardWaveform */
#define	AG33250_ATTR_FUNC_DUTY_CYCLE_HIGH               (IVI_CLASS_ATTR_BASE + 106L)  /* ViReal64, read-write */
#define	AG33250_ATTR_FUNC_AMPLITUDE                     (IVI_CLASS_ATTR_BASE + 102L)  /* ViReal64, read-write */
#define	AG33250_ATTR_FUNC_DC_OFFSET                     (IVI_CLASS_ATTR_BASE + 103L)  /* ViReal64, read-write */
#define	AG33250_ATTR_FUNC_FREQUENCY                     (IVI_CLASS_ATTR_BASE + 104L)  /* ViReal64, read-write */
#define	AG33250_ATTR_FUNC_START_PHASE                   (IVI_CLASS_ATTR_BASE + 105L)  /* ViReal64, read-write */
#define	AG33250_ATTR_FUNC_WAVEFORM                      (IVI_CLASS_ATTR_BASE + 101L)  /* ViInt32, read-write */

    /*- AM */
#define	AG33250_ATTR_AM_ENABLED                         (IVI_CLASS_ATTR_BASE + 401L)   /* ViBoolean, read-write */
#define	AG33250_ATTR_AM_SOURCE                          (IVI_CLASS_ATTR_BASE + 402L)   /* ViInt32, read-write */
#define	AG33250_ATTR_AM_INTERNAL_DEPTH                  (IVI_CLASS_ATTR_BASE + 403L)   /* ViReal64, read-write */
#define	AG33250_ATTR_AM_INTERNAL_FREQUENCY              (IVI_CLASS_ATTR_BASE + 405L)   /* ViReal64, read-write */
#define	AG33250_ATTR_AM_INTERNAL_WAVEFORM               (IVI_CLASS_ATTR_BASE + 404L)   /* ViInt32, read-write */
#define	AG33250_ATTR_AM_DEPTH                           (IVI_SPECIFIC_ATTR_BASE + 1L)  /* ViReal64, read-write */
#define	AG33250_ATTR_AM_DEPTH_MAX                       (IVI_SPECIFIC_ATTR_BASE + 2L)  /* ViReal64, read-only */
#define	AG33250_ATTR_AM_DEPTH_MIN                       (IVI_SPECIFIC_ATTR_BASE + 3L)  /* ViReal64, read-only */
#define	AG33250_ATTR_AM_INTERNAL_FREQUENCY_MAX          (IVI_SPECIFIC_ATTR_BASE + 5L)  /* ViReal64, read-only */
#define	AG33250_ATTR_AM_INTERNAL_FREQUENCY_MIN          (IVI_SPECIFIC_ATTR_BASE + 6L)  /* ViReal64, read-only */
#define	AG33250_ATTR_AM_INTERNAL_FUNCTION               (IVI_SPECIFIC_ATTR_BASE + 7L)  /* ViInt32, read-write */
#define	AG33250_ATTR_AM_STATE                           (IVI_SPECIFIC_ATTR_BASE + 9L)  /* ViBoolean, read-write */

    /*- FM */
#define	AG33250_ATTR_FM_ENABLED                         (IVI_CLASS_ATTR_BASE + 501L)    /* ViBoolean, read-write */
#define	AG33250_ATTR_FM_SOURCE                          (IVI_CLASS_ATTR_BASE + 502L)    /* ViInt32, read-write */
#define	AG33250_ATTR_FM_INTERNAL_DEVIATION              (IVI_CLASS_ATTR_BASE + 503L)    /* ViReal64, read-write */
#define	AG33250_ATTR_FM_INTERNAL_FREQUENCY              (IVI_CLASS_ATTR_BASE + 505L)    /* ViReal64, read-write */
#define	AG33250_ATTR_FM_INTERNAL_WAVEFORM               (IVI_CLASS_ATTR_BASE + 504L)    /* ViInt32, read-write */
#define	AG33250_ATTR_FM_DEVIATION                       (IVI_SPECIFIC_ATTR_BASE + 45L)  /* ViReal64, read-write */
#define	AG33250_ATTR_FM_DEVIATION_MAX                   (IVI_SPECIFIC_ATTR_BASE + 46L)  /* ViReal64, read-only */
#define	AG33250_ATTR_FM_DEVIATION_MIN                   (IVI_SPECIFIC_ATTR_BASE + 47L)  /* ViReal64, read-only */
#define	AG33250_ATTR_FM_INTERNAL_FREQUENCY_MAX          (IVI_SPECIFIC_ATTR_BASE + 49L)  /* ViReal64, read-only */
#define	AG33250_ATTR_FM_INTERNAL_FREQUENCY_MIN          (IVI_SPECIFIC_ATTR_BASE + 50L)  /* ViReal64, read-only */
#define	AG33250_ATTR_FM_INTERNAL_FUNCTION               (IVI_SPECIFIC_ATTR_BASE + 51L)  /* ViInt32, read-write */
#define	AG33250_ATTR_FM_STATE                           (IVI_SPECIFIC_ATTR_BASE + 53L)  /* ViBoolean, read-write */

    /*- ArbitraryWaveform */
#define	AG33250_ATTR_ARBITRARYWAVEFORM_NON_VOLATILE_FREE     (IVI_SPECIFIC_ATTR_BASE + 10L)  /* ViInt32, read-only */
#define	AG33250_ATTR_ARBITRARYWAVEFORM_NON_VOLATILE_MAX      (IVI_SPECIFIC_ATTR_BASE + 11L)  /* ViInt32, read-only */
#define	AG33250_ATTR_ARBITRARYWAVEFORM_USER                  (IVI_SPECIFIC_ATTR_BASE + 12L)  /* ViString, read-write */

    /*- Attribute */
#define	AG33250_ATTR_ARBITRARYWAVEFORM_ATTRIBUTE_AVERAGE              (IVI_SPECIFIC_ATTR_BASE + 13L)  /* ViReal64, read-only */
#define	AG33250_ATTR_ARBITRARYWAVEFORM_ATTRIBUTE_CREST_FACTOR         (IVI_SPECIFIC_ATTR_BASE + 14L)  /* ViReal64, read-only */
#define	AG33250_ATTR_ARBITRARYWAVEFORM_ATTRIBUTE_NUMBER_OF_POINTS     (IVI_SPECIFIC_ATTR_BASE + 15L)  /* ViInt32, read-only */
#define	AG33250_ATTR_ARBITRARYWAVEFORM_ATTRIBUTE_PEAK_TO_PEAK         (IVI_SPECIFIC_ATTR_BASE + 16L)  /* ViReal64, read-only */

    /*- Burst */
#define	AG33250_ATTR_BURST_GATE_POLARITY                (IVI_SPECIFIC_ATTR_BASE + 17L)  /* ViInt32, read-write */
#define	AG33250_ATTR_BURST_INTERNAL_PERIOD              (IVI_SPECIFIC_ATTR_BASE + 18L)  /* ViReal64, read-write */
#define	AG33250_ATTR_BURST_INTERNAL_PERIOD_MAX          (IVI_SPECIFIC_ATTR_BASE + 19L)  /* ViReal64, read-only */
#define	AG33250_ATTR_BURST_INTERNAL_PERIOD_MIN          (IVI_SPECIFIC_ATTR_BASE + 20L)  /* ViReal64, read-only */
#define	AG33250_ATTR_BURST_MODE                         (IVI_SPECIFIC_ATTR_BASE + 21L)  /* ViInt32, read-write */
#define	AG33250_ATTR_BURST_NUMBER_OF_CYCLES             (IVI_SPECIFIC_ATTR_BASE + 22L)  /* ViInt32, read-write */
#define	AG33250_ATTR_BURST_NUMBER_OF_CYCLES_MAX         (IVI_SPECIFIC_ATTR_BASE + 23L)  /* ViInt32, read-only */
#define	AG33250_ATTR_BURST_NUMBER_OF_CYCLES_MIN         (IVI_SPECIFIC_ATTR_BASE + 24L)  /* ViInt32, read-only */
#define	AG33250_ATTR_BURST_PHASE                        (IVI_SPECIFIC_ATTR_BASE + 25L)  /* ViReal64, read-write */
#define	AG33250_ATTR_BURST_PHASE_MAX                    (IVI_SPECIFIC_ATTR_BASE + 26L)  /* ViReal64, read-only */
#define	AG33250_ATTR_BURST_PHASE_MIN                    (IVI_SPECIFIC_ATTR_BASE + 27L)  /* ViReal64, read-only */
#define	AG33250_ATTR_BURST_PHASE_UNITS                  (IVI_SPECIFIC_ATTR_BASE + 28L)  /* ViInt32, read-write */
#define	AG33250_ATTR_BURST_STATE                        (IVI_SPECIFIC_ATTR_BASE + 29L)  /* ViBoolean, read-write */

    /*- Calibration */
#define	AG33250_ATTR_CALIBRATION_COUNT                  (IVI_SPECIFIC_ATTR_BASE + 37L)  /* ViInt32, read-only */
#define	AG33250_ATTR_CALIBRATION_SECURE_CODE            (IVI_SPECIFIC_ATTR_BASE + 38L)  /* ViString, write-only */
#define	AG33250_ATTR_CALIBRATION_SECURE_STATE           (IVI_SPECIFIC_ATTR_BASE + 39L)  /* ViBoolean, read-only */
#define	AG33250_ATTR_CALIBRATION_SETUP                  (IVI_SPECIFIC_ATTR_BASE + 40L)  /* ViInt32, read-write */
#define	AG33250_ATTR_CALIBRATION_STRING                 (IVI_SPECIFIC_ATTR_BASE + 41L)  /* ViString, read-write */
#define	AG33250_ATTR_CALIBRATION_VALUE                  (IVI_SPECIFIC_ATTR_BASE + 42L)  /* ViReal64, read-write */

    /*- Display */
#define	AG33250_ATTR_DISPLAY_ENABLED                    (IVI_SPECIFIC_ATTR_BASE + 43L)  /* ViBoolean, read-write */
#define	AG33250_ATTR_DISPLAY_TEXT                       (IVI_SPECIFIC_ATTR_BASE + 44L)  /* ViString, read-write */

    /*- FSK */
#define	AG33250_ATTR_FSK_FREQUENCY                      (IVI_SPECIFIC_ATTR_BASE + 54L)  /* ViReal64, read-write */
#define	AG33250_ATTR_FSK_FREQUENCY_MAX                  (IVI_SPECIFIC_ATTR_BASE + 55L)  /* ViReal64, read-only */
#define	AG33250_ATTR_FSK_FREQUENCY_MIN                  (IVI_SPECIFIC_ATTR_BASE + 56L)  /* ViReal64, read-only */
#define	AG33250_ATTR_FSK_INTERNAL_RATE                  (IVI_SPECIFIC_ATTR_BASE + 57L)  /* ViReal64, read-write */
#define	AG33250_ATTR_FSK_INTERNAL_RATE_MAX              (IVI_SPECIFIC_ATTR_BASE + 58L)  /* ViReal64, read-only */
#define	AG33250_ATTR_FSK_INTERNAL_RATE_MIN              (IVI_SPECIFIC_ATTR_BASE + 59L)  /* ViReal64, read-only */
#define	AG33250_ATTR_FSK_SOURCE                         (IVI_SPECIFIC_ATTR_BASE + 60L)  /* ViInt32, read-write */
#define	AG33250_ATTR_FSK_STATE                          (IVI_SPECIFIC_ATTR_BASE + 61L)  /* ViBoolean, read-write */

    /*- OutputTrigger */
#define	AG33250_ATTR_OUTPUTTRIGGER_SLOPE                (IVI_SPECIFIC_ATTR_BASE + 30L)  /* ViInt32, read-write */
#define	AG33250_ATTR_OUTPUTTRIGGER_STATE                (IVI_SPECIFIC_ATTR_BASE + 31L)  /* ViBoolean, read-write */

    /*- PhaseLock */
#define	AG33250_ATTR_PHASELOCK_PHASE                    (IVI_SPECIFIC_ATTR_BASE + 92L)  /* ViReal64, read-write */
#define	AG33250_ATTR_PHASELOCK_PHASE_MAX                (IVI_SPECIFIC_ATTR_BASE + 93L)  /* ViReal64, read-only */
#define	AG33250_ATTR_PHASELOCK_PHASE_MIN                (IVI_SPECIFIC_ATTR_BASE + 94L)  /* ViReal64, read-only */
#define	AG33250_ATTR_PHASELOCK_PHASE_UNITS              (IVI_SPECIFIC_ATTR_BASE + 95L)  /* ViInt32, read-write */
#define	AG33250_ATTR_PHASELOCK_UNLOCK_ERROR_STATE       (IVI_SPECIFIC_ATTR_BASE + 96L)  /* ViBoolean, read-write */

    /*- Pulse */
#define	AG33250_ATTR_PULSE_PERIOD                       (IVI_SPECIFIC_ATTR_BASE + 97L)   /* ViReal64, read-write */
#define	AG33250_ATTR_PULSE_PERIOD_MAX                   (IVI_SPECIFIC_ATTR_BASE + 98L)   /* ViReal64, read-only */
#define	AG33250_ATTR_PULSE_PERIOD_MIN                   (IVI_SPECIFIC_ATTR_BASE + 99L)   /* ViReal64, read-only */
#define	AG33250_ATTR_PULSE_TRANSITION                   (IVI_SPECIFIC_ATTR_BASE + 100L)  /* ViReal64, read-write */
#define	AG33250_ATTR_PULSE_TRANSITION_MAX               (IVI_SPECIFIC_ATTR_BASE + 101L)  /* ViReal64, read-only */
#define	AG33250_ATTR_PULSE_TRANSITION_MIN               (IVI_SPECIFIC_ATTR_BASE + 102L)  /* ViReal64, read-only */
#define	AG33250_ATTR_PULSE_WIDTH                        (IVI_SPECIFIC_ATTR_BASE + 103L)  /* ViReal64, read-write */
#define	AG33250_ATTR_PULSE_WIDTH_MAX                    (IVI_SPECIFIC_ATTR_BASE + 104L)  /* ViReal64, read-only */
#define	AG33250_ATTR_PULSE_WIDTH_MIN                    (IVI_SPECIFIC_ATTR_BASE + 105L)  /* ViReal64, read-only */

    /*- StateStorage */
#define	AG33250_ATTR_STATESTORAGE_AUTO_RECALL           (IVI_SPECIFIC_ATTR_BASE + 106L)  /* ViBoolean, read-write */
#define	AG33250_ATTR_STATESTORAGE_NUMBER_OF_STATES      (IVI_SPECIFIC_ATTR_BASE + 107L)  /* ViInt32, read-only */

    /*- Status */
#define	AG33250_ATTR_STATUS_SERIAL_POLL                 (IVI_SPECIFIC_ATTR_BASE + 108L)  /* ViInt32, read-only */

    /*- Sweep */
#define	AG33250_ATTR_SWEEP_SPACING                      (IVI_SPECIFIC_ATTR_BASE + 109L)  /* ViInt32, read-write */
#define	AG33250_ATTR_SWEEP_STATE                        (IVI_SPECIFIC_ATTR_BASE + 110L)  /* ViBoolean, read-write */
#define	AG33250_ATTR_SWEEP_TIME                         (IVI_SPECIFIC_ATTR_BASE + 111L)  /* ViReal64, read-write */
#define	AG33250_ATTR_SWEEP_TIME_MAX                     (IVI_SPECIFIC_ATTR_BASE + 112L)  /* ViReal64, read-only */
#define	AG33250_ATTR_SWEEP_TIME_MIN                     (IVI_SPECIFIC_ATTR_BASE + 113L)  /* ViReal64, read-only */

    /*- Frequency */
#define	AG33250_ATTR_SWEEP_FREQUENCY_CENTER             (IVI_SPECIFIC_ATTR_BASE + 114L)  /* ViReal64, read-write */
#define	AG33250_ATTR_SWEEP_FREQUENCY_CENTER_MAX         (IVI_SPECIFIC_ATTR_BASE + 115L)  /* ViReal64, read-only */
#define	AG33250_ATTR_SWEEP_FREQUENCY_CENTER_MIN         (IVI_SPECIFIC_ATTR_BASE + 116L)  /* ViReal64, read-only */
#define	AG33250_ATTR_SWEEP_FREQUENCY_SPAN               (IVI_SPECIFIC_ATTR_BASE + 117L)  /* ViReal64, read-write */
#define	AG33250_ATTR_SWEEP_FREQUENCY_SPAN_MAX           (IVI_SPECIFIC_ATTR_BASE + 118L)  /* ViReal64, read-only */
#define	AG33250_ATTR_SWEEP_FREQUENCY_SPAN_MIN           (IVI_SPECIFIC_ATTR_BASE + 119L)  /* ViReal64, read-only */
#define	AG33250_ATTR_SWEEP_FREQUENCY_START              (IVI_SPECIFIC_ATTR_BASE + 120L)  /* ViReal64, read-write */
#define	AG33250_ATTR_SWEEP_FREQUENCY_START_MAX          (IVI_SPECIFIC_ATTR_BASE + 121L)  /* ViReal64, read-only */
#define	AG33250_ATTR_SWEEP_FREQUENCY_START_MIN          (IVI_SPECIFIC_ATTR_BASE + 122L)  /* ViReal64, read-only */
#define	AG33250_ATTR_SWEEP_FREQUENCY_STOP               (IVI_SPECIFIC_ATTR_BASE + 123L)  /* ViReal64, read-write */
#define	AG33250_ATTR_SWEEP_FREQUENCY_STOP_MAX           (IVI_SPECIFIC_ATTR_BASE + 124L)  /* ViReal64, read-only */
#define	AG33250_ATTR_SWEEP_FREQUENCY_STOP_MIN           (IVI_SPECIFIC_ATTR_BASE + 125L)  /* ViReal64, read-only */

    /*- Marker */
#define	AG33250_ATTR_SWEEP_MARKER_FREQUENCY             (IVI_SPECIFIC_ATTR_BASE + 126L)  /* ViReal64, read-write */
#define	AG33250_ATTR_SWEEP_MARKER_FREQUENCY_MAX         (IVI_SPECIFIC_ATTR_BASE + 127L)  /* ViReal64, read-only */
#define	AG33250_ATTR_SWEEP_MARKER_FREQUENCY_MIN         (IVI_SPECIFIC_ATTR_BASE + 128L)  /* ViReal64, read-only */
#define	AG33250_ATTR_SWEEP_MARKER_STATE                 (IVI_SPECIFIC_ATTR_BASE + 129L)  /* ViBoolean, read-write */

    /*- System */
#define	AG33250_ATTR_SYSTEM_ASYNC_EVENTS_ENABLED        (IVI_SPECIFIC_ATTR_BASE + 130L)  /* ViBoolean, read-write */
#define	AG33250_ATTR_SYSTEM_BEEPER_STATE                (IVI_SPECIFIC_ATTR_BASE + 131L)  /* ViBoolean, read-write */
#define	AG33250_ATTR_SYSTEM_SERIAL_NUMBER               (IVI_SPECIFIC_ATTR_BASE + 132L)  /* ViString, read-only */
#define	AG33250_ATTR_SYSTEM_TIMEOUT_MILLISECONDS        (IVI_SPECIFIC_ATTR_BASE + 133L)  /* ViInt32, read-write */
#define	AG33250_ATTR_SYSTEM_TRACE_ENABLED               (IVI_SPECIFIC_ATTR_BASE + 134L)  /* ViBoolean, read-write */
		


/**************************************************************************** 
 *------------------------ Attribute Value Defines -------------------------* 
 ****************************************************************************/

    /*- Defined values for attribute AG33250_ATTR_OUTPUT_MODE */
#define	AG33250_VAL_OUTPUT_FUNC                         0
#define	AG33250_VAL_OUTPUT_ARB                          1
#define	AG33250_VAL_OUTPUT_SEQ                          2

    /*- Defined values for attribute AG33250_ATTR_OPERATION_MODE */
#define	AG33250_VAL_OPERATE_CONTINUOUS                  0
#define	AG33250_VAL_OPERATE_BURST                       1

    /*- Defined values for attribute AG33250_ATTR_REF_CLOCK_SOURCE */
#define	AG33250_VAL_REF_CLOCK_INTERNAL                  0
#define	AG33250_VAL_REF_CLOCK_EXTERNAL                  1
#define	AG33250_VAL_REF_CLOCK_RTSI_CLOCK                101

    /*- Defined values for attribute AG33250_ATTR_TRIGGER_SOURCE */
#define	AG33250_VAL_EXTERNAL                            1
#define	AG33250_VAL_SOFTWARE_TRIG                       2
#define	AG33250_VAL_INTERNAL_TRIGGER                    3
#define	AG33250_VAL_TTL0                                111
#define	AG33250_VAL_TTL1                                112
#define	AG33250_VAL_TTL2                                113
#define	AG33250_VAL_TTL3                                114
#define	AG33250_VAL_TTL4                                115
#define	AG33250_VAL_TTL5                                116
#define	AG33250_VAL_TTL6                                117
#define	AG33250_VAL_TTL7                                118
#define	AG33250_VAL_ECL0                                119
#define	AG33250_VAL_ECL1                                120
#define	AG33250_VAL_PXI_STAR                            131
#define	AG33250_VAL_RTSI_0                              141
#define	AG33250_VAL_RTSI_1                              142
#define	AG33250_VAL_RTSI_2                              143
#define	AG33250_VAL_RTSI_3                              144
#define	AG33250_VAL_RTSI_4                              145
#define	AG33250_VAL_RTSI_5                              146
#define	AG33250_VAL_RTSI_6                              147

    /*- Defined values for attribute AG33250_ATTR_FUNC_WAVEFORM, parameter Waveform in function Ag33250_ConfigureStandardWaveform */
#define	AG33250_VAL_WFM_SINE                            1
#define	AG33250_VAL_WFM_SQUARE                          2
#define	AG33250_VAL_WFM_TRIANGLE                        3
#define	AG33250_VAL_WFM_RAMP_UP                         4
#define	AG33250_VAL_WFM_RAMP_DOWN                       5
#define	AG33250_VAL_WFM_DC                              6

    /*- Defined values for attribute AG33250_ATTR_AM_SOURCE */
#define	AG33250_VAL_AM_INTERNAL                         0
#define	AG33250_VAL_AM_EXTERNAL                         1

    /*- Defined values for attribute AG33250_ATTR_AM_INTERNAL_WAVEFORM, parameter Waveform in function Ag33250_ConfigureAMInternal */
#define	AG33250_VAL_AM_INTERNAL_SINE                    1
#define	AG33250_VAL_AM_INTERNAL_SQUARE                  2
#define	AG33250_VAL_AM_INTERNAL_TRIANGLE                3
#define	AG33250_VAL_AM_INTERNAL_RAMP_UP                 4
#define	AG33250_VAL_AM_INTERNAL_RAMP_DOWN               5

    /*- Defined values for attribute AG33250_ATTR_FM_SOURCE */
#define	AG33250_VAL_FM_INTERNAL                         0
#define	AG33250_VAL_FM_EXTERNAL                         1

    /*- Defined values for attribute AG33250_ATTR_FM_INTERNAL_WAVEFORM, parameter Waveform in function Ag33250_ConfigureFMInternal */
#define	AG33250_VAL_FM_INTERNAL_SINE                    1
#define	AG33250_VAL_FM_INTERNAL_SQUARE                  2
#define	AG33250_VAL_FM_INTERNAL_TRIANGLE                3
#define	AG33250_VAL_FM_INTERNAL_RAMP_UP                 4
#define	AG33250_VAL_FM_INTERNAL_RAMP_DOWN               5

    /*- Defined values for attribute AG33250_ATTR_AM_INTERNAL_FUNCTION */
#define	AG33250_VAL_AM_INTERNAL_FUNCTION_SINUSOID       0
#define	AG33250_VAL_AM_INTERNAL_FUNCTION_SQUARE         1
#define	AG33250_VAL_AM_INTERNAL_FUNCTION_RAMP           2
#define	AG33250_VAL_AM_INTERNAL_FUNCTION_NEGATIVE_RAMP  3
#define	AG33250_VAL_AM_INTERNAL_FUNCTION_TRIANGLE       4
#define	AG33250_VAL_AM_INTERNAL_FUNCTION_NOISE          5
#define	AG33250_VAL_AM_INTERNAL_FUNCTION_USER           6

    /*- Defined values for attribute AG33250_ATTR_BURST_GATE_POLARITY */
#define	AG33250_VAL_BURST_GATE_POLARITY_NORMAL          0
#define	AG33250_VAL_BURST_GATE_POLARITY_INVERTED        1

    /*- Defined values for attribute AG33250_ATTR_BURST_MODE */
#define	AG33250_VAL_BURST_MODE_TRIGGERED                0
#define	AG33250_VAL_BURST_MODE_GATED                    1

    /*- Defined values for attribute AG33250_ATTR_BURST_PHASE_UNITS, attribute AG33250_ATTR_PHASELOCK_PHASE_UNITS */
#define	AG33250_VAL_PHASE_UNIT_DEGREE                   0
#define	AG33250_VAL_PHASE_UNIT_RADIAN                   1

    /*- Defined values for attribute AG33250_ATTR_FM_INTERNAL_FUNCTION */
#define	AG33250_VAL_FM_INTERNAL_FUNCTION_SINUSOID       0
#define	AG33250_VAL_FM_INTERNAL_FUNCTION_SQUARE         1
#define	AG33250_VAL_FM_INTERNAL_FUNCTION_RAMP           2
#define	AG33250_VAL_FM_INTERNAL_FUNCTION_NEGATIVE_RAMP  3
#define	AG33250_VAL_FM_INTERNAL_FUNCTION_TRIANGLE       4
#define	AG33250_VAL_FM_INTERNAL_FUNCTION_NOISE          5
#define	AG33250_VAL_FM_INTERNAL_FUNCTION_USER           6

    /*- Defined values for attribute AG33250_ATTR_FSK_SOURCE */
#define	AG33250_VAL_FSK_SOURCE_INTERNAL                 0
#define	AG33250_VAL_FSK_SOURCE_EXTERNAL                 1

    /*- Defined values for attribute AG33250_ATTR_OUTPUT_FUNCTION, parameter pFunction in function Ag33250_ApplyQuery */
#define	AG33250_VAL_OUTPUT_FUNCTION_SINUSOID            0
#define	AG33250_VAL_OUTPUT_FUNCTION_SQUARE              1
#define	AG33250_VAL_OUTPUT_FUNCTION_RAMP                2
#define	AG33250_VAL_OUTPUT_FUNCTION_PULSE               3
#define	AG33250_VAL_OUTPUT_FUNCTION_NOISE               4
#define	AG33250_VAL_OUTPUT_FUNCTION_DC                  5
#define	AG33250_VAL_OUTPUT_FUNCTION_USER                6

    /*- Defined values for attribute AG33250_ATTR_OUTPUT_POLARITY */
#define	AG33250_VAL_OUTPUT_POLARITY_NORMAL              0
#define	AG33250_VAL_OUTPUT_POLARITY_INVERTED            1

    /*- Defined values for attribute AG33250_ATTR_OUTPUTTRIGGER_SLOPE, attribute AG33250_ATTR_TRIGGER_SLOPE */
#define	AG33250_VAL_TRIGGER_SLOPE_POSITIVE              0
#define	AG33250_VAL_TRIGGER_SLOPE_NEGATIVE              1

    /*- Defined values for attribute AG33250_ATTR_OUTPUT_VOLTAGE_RANGE_AUTO */
#define	AG33250_VAL_VOLTAGE_RANGE_AUTO_OFF              0
#define	AG33250_VAL_VOLTAGE_RANGE_AUTO_ON               1
#define	AG33250_VAL_VOLTAGE_RANGE_AUTO_ONCE             2

    /*- Defined values for attribute AG33250_ATTR_OUTPUT_VOLTAGE_UNITS */
#define	AG33250_VAL_OUTPUT_VOLTAGE_UNIT_VPP             0
#define	AG33250_VAL_OUTPUT_VOLTAGE_UNIT_VRMS            1
#define	AG33250_VAL_OUTPUT_VOLTAGE_UNIT_DBM             2

    /*- Defined values for attribute AG33250_ATTR_SWEEP_SPACING */
#define	AG33250_VAL_SWEEP_SPACING_LINEAR                0
#define	AG33250_VAL_SWEEP_SPACING_LOGARITHMIC           1

    /*- Defined values for parameter retVal in function Ag33250_CalibrationCalibrate */
#define	AG33250_VAL_CALIBRATION_RESULT_PASSED           0
#define	AG33250_VAL_CALIBRATION_RESULT_FAILED           1

    /*- Defined values for parameter Reason in function Ag33250_StatusConfigureServiceRequest */
#define	AG33250_VAL_SRQ_REASON_STB_MAV                  1
#define	AG33250_VAL_SRQ_REASON_STB_ERROR_QUE            2
#define	AG33250_VAL_SRQ_REASON_ESR_OPC                  4
#define	AG33250_VAL_SRQ_REASON_ESR_QUERY_ERROR          8
#define	AG33250_VAL_SRQ_REASON_ESR_DEVICE_ERROR         16
#define	AG33250_VAL_SRQ_REASON_ESR_EXECUTION_ERROR      32
#define	AG33250_VAL_SRQ_REASON_ESR_COMMAND_ERROR        64
#define	AG33250_VAL_SRQ_REASON_ESR_POWER_ON             128
#define	AG33250_VAL_SRQ_REASON_QUES_VOLTAGE             256
#define	AG33250_VAL_SRQ_REASON_QUES_TEMPERATURE         1024
#define	AG33250_VAL_SRQ_REASON_QUES_FREQUENCY           2048
#define	AG33250_VAL_SRQ_REASON_QUES_PHASE               4096
#define	AG33250_VAL_SRQ_REASON_QUES_MODULATION          8192
#define	AG33250_VAL_SRQ_REASON_QUES_CALIBRATION         16384
#define	AG33250_VAL_SRQ_REASON_QUES_EXTERNAL_TIMEBASE   32768

    /*- Defined values for parameter Register in function Ag33250_StatusGetRegister, 
        parameter Register in function Ag33250_StatusSetRegister */
#define	AG33250_VAL_STATUS_REGISTER_STATUS_BYTE         0
#define	AG33250_VAL_STATUS_REGISTER_STANDARD_EVENT      1
#define	AG33250_VAL_STATUS_REGISTER_QUESTIONABLE        2

    /*- Defined values for parameter SubRegister in function Ag33250_StatusGetRegister, 
        parameter SubRegister in function Ag33250_StatusSetRegister */
#define	AG33250_VAL_STATUS_SUB_REGISTER_CONDITION       0
#define	AG33250_VAL_STATUS_SUB_REGISTER_EVENT           1
#define	AG33250_VAL_STATUS_SUB_REGISTER_ENABLE          2



/**************************************************************************** 
 *---------------- Instrument Driver Function Declarations -----------------* 
 ****************************************************************************/

    /*- Agilent33250 */

ViStatus _VI_FUNC  Ag33250_init ( ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViSession* Vi );

ViStatus _VI_FUNC  Ag33250_GetNativeIUnknownPtr ( ViSession Vi, IUnknown** NativeIUnknownPtr );

ViStatus _VI_FUNC  Ag33250_close ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_InitWithOptions ( ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViConstString OptionsString, ViSession* Vi );

    /*- System */

ViStatus _VI_FUNC  Ag33250_SystemRead ( ViSession Vi, ViInt32 Size, ViChar Value[], ViInt32* ActualSize );

ViStatus _VI_FUNC  Ag33250_SystemWrite ( ViSession Vi, ViConstString CommandString );

ViStatus _VI_FUNC  Ag33250_SystemWaitForOperationComplete ( ViSession Vi, ViInt32 MaxTimeMilliseconds );

ViStatus _VI_FUNC  Ag33250_SystemSaveState ( ViSession Vi, ViConstString Identifier );

ViStatus _VI_FUNC  Ag33250_SystemRecallState ( ViSession Vi, ViConstString Identifier );

ViStatus _VI_FUNC  Ag33250_SystemPutState ( ViSession Vi, ViInt32 DataBufferSize, ViChar Data[], ViInt32* DataActualSize );

ViStatus _VI_FUNC  Ag33250_SystemGetState ( ViSession Vi, ViInt32 pDataBufferSize, ViChar pData[], ViInt32* pDataActualSize );

ViStatus _VI_FUNC  Ag33250_SystemEnableLocalControls ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_SystemDisableLocalControls ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_SystemBeeper ( ViSession Vi );

    /*- ArbitraryWaveform */

ViStatus _VI_FUNC  Ag33250_ArbitraryWaveformQueryCatalog ( ViSession Vi, ViInt32 retValBufferSize, ViChar retVal[] );

ViStatus _VI_FUNC  Ag33250_ArbitraryWaveformQueryNonVolatileCatalog ( ViSession Vi, ViInt32 retValBufferSize, ViChar retVal[] );

ViStatus _VI_FUNC  Ag33250_ArbitraryWaveformSetUser ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_ArbitraryWaveformSetDataDAC ( ViSession Vi, ViInt32 ValBufferSize, ViInt16 Val[], ViInt32* ValActualSize );

ViStatus _VI_FUNC  Ag33250_ArbitraryWaveformSetData ( ViSession Vi, ViInt32 ValBufferSize, ViReal64 Val[], ViInt32* ValActualSize );

ViStatus _VI_FUNC  Ag33250_ArbitraryWaveformDeleteAll ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_ArbitraryWaveformDelete ( ViSession Vi, ViConstString Name );

ViStatus _VI_FUNC  Ag33250_ArbitraryWaveformCopyData ( ViSession Vi, ViConstString Name );

    /*- Utility */

ViStatus _VI_FUNC  Ag33250_revision_query ( ViSession Vi, ViChar DriverRev[], ViChar InstrRev[] );

ViStatus _VI_FUNC  Ag33250_error_message ( ViSession Vi, ViStatus ErrorCode, ViChar ErrorMessage[] );

ViStatus _VI_FUNC  Ag33250_AttachToExistingCOMSession ( IUnknown* ExistingIUnknownPtr, ViSession* Vi );

ViStatus _VI_FUNC  Ag33250_GetError ( ViSession Vi, ViStatus* ErrorCode, ViInt32 ErrorDescriptionBufferSize, ViChar ErrorDescription[] );

ViStatus _VI_FUNC  Ag33250_ClearError ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_GetChannelName ( ViSession Vi, ViInt32 Index, ViInt32 NameBufferSize, ViChar Name[] );

ViStatus _VI_FUNC  Ag33250_GetNextCoercionRecord ( ViSession Vi, ViInt32 CoercionRecordBufferSize, ViChar CoercionRecord[] );

ViStatus _VI_FUNC  Ag33250_ResetInterchangeCheck ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_GetNextInterchangeWarning ( ViSession Vi, ViInt32 InterchangeWarningBufferSize, ViChar InterchangeWarning[] );

ViStatus _VI_FUNC  Ag33250_ClearInterchangeWarnings ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_InvalidateAllAttributes ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_UnlockSession ( ViSession Vi, ViBoolean* CallerHasLock );

ViStatus _VI_FUNC  Ag33250_LockSession ( ViSession Vi, ViBoolean* CallerHasLock );

ViStatus _VI_FUNC  Ag33250_error_query ( ViSession Vi, ViInt32* ErrorCode, ViChar ErrorMessage[] );

ViStatus _VI_FUNC  Ag33250_self_test ( ViSession Vi, ViInt16* TestResult, ViChar TestMessage[] );

ViStatus _VI_FUNC  Ag33250_Disable ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_ResetWithDefaults ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_reset ( ViSession Vi );

    /*- Attribute Accessors */

ViStatus _VI_FUNC  Ag33250_GetAttributeViInt32 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32* AttributeValue );

ViStatus _VI_FUNC  Ag33250_GetAttributeViReal64 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64* AttributeValue );

ViStatus _VI_FUNC  Ag33250_GetAttributeViBoolean ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean* AttributeValue );

ViStatus _VI_FUNC  Ag33250_GetAttributeViSession ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession* AttributeValue );

ViStatus _VI_FUNC  Ag33250_GetAttributeViString ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[] );

ViStatus _VI_FUNC  Ag33250_SetAttributeViInt32 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValue );

ViStatus _VI_FUNC  Ag33250_SetAttributeViReal64 ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViReal64 AttributeValue );

ViStatus _VI_FUNC  Ag33250_SetAttributeViBoolean ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViBoolean AttributeValue );

ViStatus _VI_FUNC  Ag33250_SetAttributeViSession ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession AttributeValue );

ViStatus _VI_FUNC  Ag33250_SetAttributeViString ( ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViConstString AttributeValue );

    /*- General */

ViStatus _VI_FUNC  Ag33250_ConfigureOperationMode ( ViSession Vi, ViConstString ChannelName, ViInt32 OperationMode );

ViStatus _VI_FUNC  Ag33250_ConfigureOutputEnabled ( ViSession Vi, ViConstString ChannelName, ViBoolean Enabled );

ViStatus _VI_FUNC  Ag33250_ConfigureOutputImpedance ( ViSession Vi, ViConstString ChannelName, ViReal64 Impedance );

ViStatus _VI_FUNC  Ag33250_ConfigureOutputMode ( ViSession Vi, ViInt32 OutputMode );

ViStatus _VI_FUNC  Ag33250_ConfigureRefClockSource ( ViSession Vi, ViInt32 Source );

    /*- Arbitrary Waveform */

ViStatus _VI_FUNC  Ag33250_ConfigureSampleRate ( ViSession Vi, ViReal64 SampleRate );

ViStatus _VI_FUNC  Ag33250_QueryArbWfmCapabilities ( ViSession Vi, ViInt32* MaxNumWfms, ViInt32* WfmQuantum, ViInt32* MinWfmSize, ViInt32* MaxWfmSize );

ViStatus _VI_FUNC  Ag33250_CreateArbWaveform ( ViSession Vi, ViInt32 Size, ViReal64 Data[], ViInt32* Handle );

ViStatus _VI_FUNC  Ag33250_ClearArbWaveform ( ViSession Vi, ViInt32 Handle );

ViStatus _VI_FUNC  Ag33250_ConfigureArbWaveform ( ViSession Vi, ViConstString ChannelName, ViInt32 Handle, ViReal64 Gain, ViReal64 Offset );

    /*- Arbitrary Waveform Frequency */

ViStatus _VI_FUNC  Ag33250_ConfigureArbFrequency ( ViSession Vi, ViConstString ChannelName, ViReal64 Frequency );

    /*- Trigger */

ViStatus _VI_FUNC  Ag33250_ConfigureTriggerSource ( ViSession Vi, ViConstString ChannelName, ViInt32 Source );

    /*- Internal Trigger */

ViStatus _VI_FUNC  Ag33250_ConfigureInternalTriggerRate ( ViSession Vi, ViReal64 Rate );

    /*- Burst */

ViStatus _VI_FUNC  Ag33250_ConfigureBurstCount ( ViSession Vi, ViConstString ChannelName, ViInt32 Count );

    /*- Amplitude Modulation */

ViStatus _VI_FUNC  Ag33250_ConfigureAMEnabled ( ViSession Vi, ViConstString ChannelName, ViBoolean Enabled );

ViStatus _VI_FUNC  Ag33250_ConfigureAMSource ( ViSession Vi, ViConstString ChannelName, ViInt32 Source );

ViStatus _VI_FUNC  Ag33250_ConfigureAMInternal ( ViSession Vi, ViReal64 Depth, ViInt32 Waveform, ViReal64 Frequency );

    /*- Frequency Modulation */

ViStatus _VI_FUNC  Ag33250_ConfigureFMEnabled ( ViSession Vi, ViConstString ChannelName, ViBoolean Enabled );

ViStatus _VI_FUNC  Ag33250_ConfigureFMSource ( ViSession Vi, ViConstString ChannelName, ViInt32 Source );

ViStatus _VI_FUNC  Ag33250_ConfigureFMInternal ( ViSession Vi, ViReal64 Deviation, ViInt32 Waveform, ViReal64 Frequency );

    /*- Standard Waveform */

ViStatus _VI_FUNC  Ag33250_ConfigureStandardWaveform ( ViSession Vi, ViConstString ChannelName, ViInt32 Waveform, ViReal64 Amplitude, ViReal64 DCOffset, ViReal64 Frequency, ViReal64 StartPhase );

    /*- Arbitrary Sequence */

ViStatus _VI_FUNC  Ag33250_ClearArbMemory ( ViSession Vi );

    /*- Action */

ViStatus _VI_FUNC  Ag33250_SendSoftwareTrigger ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_AbortGeneration ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_InitiateGeneration ( ViSession Vi );

    /*- AM */

ViStatus _VI_FUNC  Ag33250_AMSetInternalFrequencyMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_AMSetInternalFrequencyMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_AMSetDepthMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_AMSetDepthMax ( ViSession Vi );

    /*- Apply */

ViStatus _VI_FUNC  Ag33250_ApplySetUser ( ViSession Vi, ViReal64 Frequency, ViReal64 Amplitude, ViReal64 Offset );

ViStatus _VI_FUNC  Ag33250_ApplySetSquare ( ViSession Vi, ViReal64 Frequency, ViReal64 Amplitude, ViReal64 Offset );

ViStatus _VI_FUNC  Ag33250_ApplySetSinusoid ( ViSession Vi, ViReal64 Frequency, ViReal64 Amplitude, ViReal64 Offset );

ViStatus _VI_FUNC  Ag33250_ApplySetRamp ( ViSession Vi, ViReal64 Frequency, ViReal64 Amplitude, ViReal64 Offset );

ViStatus _VI_FUNC  Ag33250_ApplySetPulse ( ViSession Vi, ViReal64 Frequency, ViReal64 Amplitude, ViReal64 Offset );

ViStatus _VI_FUNC  Ag33250_ApplySetNoise ( ViSession Vi, ViReal64 Amplitude, ViReal64 Offset );

ViStatus _VI_FUNC  Ag33250_ApplySetDC ( ViSession Vi, ViReal64 Offset );

ViStatus _VI_FUNC  Ag33250_ApplyQuery ( ViSession Vi, ViInt32* pFunction, ViReal64* pFrequency, ViReal64* pAmplitude, ViReal64* pOffset );

    /*- Burst */

ViStatus _VI_FUNC  Ag33250_BurstSetPhaseMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_BurstSetPhaseMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_BurstSetNumberOfCyclesMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_BurstSetNumberOfCyclesMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_BurstSetNumberOfCyclesInfinity ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_BurstSetInternalPeriodMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_BurstSetInternalPeriodMax ( ViSession Vi );

    /*- Calibration */

ViStatus _VI_FUNC  Ag33250_CalibrationSetSecureState ( ViSession Vi, ViBoolean Val, ViConstString Code );

ViStatus _VI_FUNC  Ag33250_CalibrationCalibrate ( ViSession Vi, ViInt32* retVal );

    /*- Display */

ViStatus _VI_FUNC  Ag33250_DisplayTextClear ( ViSession Vi );

    /*- FM */

ViStatus _VI_FUNC  Ag33250_FMSetInternalFrequencyMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_FMSetInternalFrequencyMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_FMSetDeviationMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_FMSetDeviationMax ( ViSession Vi );

    /*- FSK */

ViStatus _VI_FUNC  Ag33250_FSKSetInternalRateMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_FSKSetInternalRateMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_FSKSetFrequencyMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_FSKSetFrequencyMax ( ViSession Vi );

    /*- Output */

ViStatus _VI_FUNC  Ag33250_OutputSetSquareDutyCycleMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputSetSquareDutyCycleMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputSetRampSymmetryMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputSetRampSymmetryMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputSetLoadMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputSetLoadMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputSetLoadInfinity ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputSetFrequencyMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputSetFrequencyMax ( ViSession Vi );

    /*- Voltage */

ViStatus _VI_FUNC  Ag33250_OutputVoltageSetOffsetMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputVoltageSetOffsetMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputVoltageSetLowMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputVoltageSetLowMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputVoltageSetHighMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputVoltageSetHighMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputVoltageSetAmplitudeMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_OutputVoltageSetAmplitudeMax ( ViSession Vi );

    /*- PhaseLock */

ViStatus _VI_FUNC  Ag33250_PhaseLockSetPhaseMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_PhaseLockSetPhaseMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_PhaseLockReference ( ViSession Vi );

    /*- Pulse */

ViStatus _VI_FUNC  Ag33250_PulseSetWidthMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_PulseSetWidthMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_PulseSetTransitionMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_PulseSetTransitionMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_PulseSetPeriodMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_PulseSetPeriodMax ( ViSession Vi );

    /*- StateStorage */

ViStatus _VI_FUNC  Ag33250_StateStorageSave ( ViSession Vi, ViInt32 State );

ViStatus _VI_FUNC  Ag33250_StateStorageRecall ( ViSession Vi, ViInt32 State );

ViStatus _VI_FUNC  Ag33250_StateStorageDelete ( ViSession Vi, ViInt32 State );

ViStatus _VI_FUNC  Ag33250_StateStorageGetName ( ViSession Vi, ViInt32 State, ViInt32 retValBufferSize, ViChar retVal[] );

ViStatus _VI_FUNC  Ag33250_StateStorageSetName ( ViSession Vi, ViInt32 State, ViConstString val );

ViStatus _VI_FUNC  Ag33250_StateStorageGetValid ( ViSession Vi, ViInt32 State, ViBoolean* retVal );

    /*- Status */

ViStatus _VI_FUNC  Ag33250_StatusPreset ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_StatusConfigureServiceRequest ( ViSession Vi, ViInt32 Reason );

ViStatus _VI_FUNC  Ag33250_StatusClear ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_StatusGetRegister ( ViSession Vi, ViInt32 Register, ViInt32 SubRegister, ViInt32* retVal );

ViStatus _VI_FUNC  Ag33250_StatusSetRegister ( ViSession Vi, ViInt32 Register, ViInt32 SubRegister, ViInt32 val );

    /*- Sweep */

ViStatus _VI_FUNC  Ag33250_SweepSetTimeMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_SweepSetTimeMax ( ViSession Vi );

    /*- Frequency */

ViStatus _VI_FUNC  Ag33250_SweepFrequencySetStopMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_SweepFrequencySetStopMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_SweepFrequencySetStartMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_SweepFrequencySetStartMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_SweepFrequencySetSpanMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_SweepFrequencySetSpanMax ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_SweepFrequencySetCenterMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_SweepFrequencySetCenterMax ( ViSession Vi );

    /*- Marker */

ViStatus _VI_FUNC  Ag33250_SweepMarkerSetFrequencyMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_SweepMarkerSetFrequencyMax ( ViSession Vi );

    /*- Trigger */

ViStatus _VI_FUNC  Ag33250_TriggerTrigger ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_TriggerSoftwareTrigger ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_TriggerSetDelayMin ( ViSession Vi );

ViStatus _VI_FUNC  Ag33250_TriggerSetDelayMax ( ViSession Vi );


/**************************************************************************** 
 *----------------- Instrument Error And Completion Codes ------------------* 
 ****************************************************************************/
#ifndef _IVIC_ERROR_BASE_DEFINES_
#define _IVIC_ERROR_BASE_DEFINES_

#define IVIC_WARN_BASE                           (0x3FFA0000L)
#define IVIC_CROSS_CLASS_WARN_BASE               (IVIC_WARN_BASE + 0x1000)
#define IVIC_CLASS_WARN_BASE                     (IVIC_WARN_BASE + 0x2000)
#define IVIC_SPECIFIC_WARN_BASE                  (IVIC_WARN_BASE + 0x4000)

#define IVIC_ERROR_BASE                          (0xBFFA0000L)
#define IVIC_CROSS_CLASS_ERROR_BASE              (IVIC_ERROR_BASE + 0x1000)
#define IVIC_CLASS_ERROR_BASE                    (IVIC_ERROR_BASE + 0x2000)
#define IVIC_SPECIFIC_ERROR_BASE                 (IVIC_ERROR_BASE + 0x4000)
#define IVIC_LXISYNC_ERROR_BASE                  (IVIC_ERROR_BASE + 0x3000)

#define IVIC_ERROR_INVALID_ATTRIBUTE             (IVIC_ERROR_BASE + 0x0C)
#define IVIC_ERROR_TYPES_DO_NOT_MATCH            (IVIC_ERROR_BASE + 0x15)
#define IVIC_ERROR_IVI_ATTR_NOT_WRITABLE         (IVIC_ERROR_BASE + 0x0D)
#define IVIC_ERROR_IVI_ATTR_NOT_READABLE         (IVIC_ERROR_BASE + 0x0E)

#endif



#define AG33250_SUCCESS                                   0
#define AG33250_WARN_NSUP_ID_QUERY                        (IVIC_WARN_BASE + 0x65)
#define AG33250_WARN_NSUP_RESET                           (IVIC_WARN_BASE + 0x66)
#define AG33250_WARN_NSUP_SELF_TEST                       (IVIC_WARN_BASE + 0x67)
#define AG33250_WARN_NSUP_ERROR_QUERY                     (IVIC_WARN_BASE + 0x68)
#define AG33250_WARN_NSUP_REV_QUERY                       (IVIC_WARN_BASE + 0x69)
#define AG33250_ERROR_CANNOT_RECOVER                      (IVIC_ERROR_BASE + 0x00)
#define AG33250_ERROR_INSTRUMENT_STATUS                   (IVIC_ERROR_BASE + 0x01)
#define AG33250_ERROR_CANNOT_OPEN_FILE                    (IVIC_ERROR_BASE + 0x02)
#define AG33250_ERROR_READING_FILE                        (IVIC_ERROR_BASE + 0x03)
#define AG33250_ERROR_WRITING_FILE                        (IVIC_ERROR_BASE + 0x04)
#define AG33250_ERROR_INVALID_PATHNAME                    (IVIC_ERROR_BASE + 0x0B)
#define AG33250_ERROR_INVALID_VALUE                       (IVIC_ERROR_BASE + 0x10)
#define AG33250_ERROR_FUNCTION_NOT_SUPPORTED              (IVIC_ERROR_BASE + 0x11)
#define AG33250_ERROR_ATTRIBUTE_NOT_SUPPORTED             (IVIC_ERROR_BASE + 0x12)
#define AG33250_ERROR_VALUE_NOT_SUPPORTED                 (IVIC_ERROR_BASE + 0x13)
#define AG33250_ERROR_NOT_INITIALIZED                     (IVIC_ERROR_BASE + 0x1D)
#define AG33250_ERROR_UNKNOWN_CHANNEL_NAME                (IVIC_ERROR_BASE + 0x20)
#define AG33250_ERROR_TOO_MANY_OPEN_FILES                 (IVIC_ERROR_BASE + 0x23)
#define AG33250_ERROR_CHANNEL_NAME_REQUIRED               (IVIC_ERROR_BASE + 0x44)
#define AG33250_ERROR_MISSING_OPTION_NAME                 (IVIC_ERROR_BASE + 0x49)
#define AG33250_ERROR_MISSING_OPTION_VALUE                (IVIC_ERROR_BASE + 0x4A)
#define AG33250_ERROR_BAD_OPTION_NAME                     (IVIC_ERROR_BASE + 0x4B)
#define AG33250_ERROR_BAD_OPTION_VALUE                    (IVIC_ERROR_BASE + 0x4C)
#define AG33250_ERROR_OUT_OF_MEMORY                       (IVIC_ERROR_BASE + 0x56)
#define AG33250_ERROR_OPERATION_PENDING                   (IVIC_ERROR_BASE + 0x57)
#define AG33250_ERROR_NULL_POINTER                        (IVIC_ERROR_BASE + 0x58)
#define AG33250_ERROR_UNEXPECTED_RESPONSE                 (IVIC_ERROR_BASE + 0x59)
#define AG33250_ERROR_FILE_NOT_FOUND                      (IVIC_ERROR_BASE + 0x5B)
#define AG33250_ERROR_INVALID_FILE_FORMAT                 (IVIC_ERROR_BASE + 0x5C)
#define AG33250_ERROR_STATUS_NOT_AVAILABLE                (IVIC_ERROR_BASE + 0x5D)
#define AG33250_ERROR_ID_QUERY_FAILED                     (IVIC_ERROR_BASE + 0x5E)
#define AG33250_ERROR_RESET_FAILED                        (IVIC_ERROR_BASE + 0x5F)
#define AG33250_ERROR_RESOURCE_UNKNOWN                    (IVIC_ERROR_BASE + 0x60)
#define AG33250_ERROR_ALREADY_INITIALIZED                 (IVIC_ERROR_BASE + 0x61)
#define AG33250_ERROR_CANNOT_CHANGE_SIMULATION_STATE      (IVIC_ERROR_BASE + 0x62)
#define AG33250_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR (IVIC_ERROR_BASE + 0x63)
#define AG33250_ERROR_INVALID_RANGE_IN_SELECTOR           (IVIC_ERROR_BASE + 0x64)
#define AG33250_ERROR_UNKOWN_NAME_IN_SELECTOR             (IVIC_ERROR_BASE + 0x65)
#define AG33250_ERROR_BADLY_FORMED_SELECTOR               (IVIC_ERROR_BASE + 0x66)
#define AG33250_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER         (IVIC_ERROR_BASE + 0x67)
#define AG33250_IVIFGEN_ERROR_TRIGGER_NOT_SOFTWARE        (IVIC_CROSS_CLASS_ERROR_BASE + 1L)
#define AG33250_IVIFGEN_ERROR_NO_WFMS_AVAILABLE           (IVIC_CLASS_ERROR_BASE + 4L)
#define AG33250_IVIFGEN_ERROR_WFM_IN_USE                  (IVIC_CLASS_ERROR_BASE + 8L)
#define AG33250_IVIFGEN_ERROR_NO_SEQS_AVAILABLE           (IVIC_CLASS_ERROR_BASE + 9L)
#define AG33250_IVIFGEN_ERROR_SEQ_IN_USE                  (IVIC_CLASS_ERROR_BASE + 13L)


#define AG33250_ERROR_PERSONALITY_NOT_ACTIVE              (IVIC_SPECIFIC_ERROR_BASE + 529L)
#define AG33250_ERROR_PERSONALITY_NOT_INSTALLED           (IVIC_SPECIFIC_ERROR_BASE + 530L)
#define AG33250_ERROR_PERSONALITY_NOT_LICENSED            (IVIC_SPECIFIC_ERROR_BASE + 531L)
#define AG33250_ERROR_IO_GENERAL                          (IVIC_SPECIFIC_ERROR_BASE + 532L)
#define AG33250_ERROR_IO_TIMEOUT                          (IVIC_SPECIFIC_ERROR_BASE + 533L)
#define AG33250_ERROR_MODEL_NOT_SUPPORTED                 (IVIC_SPECIFIC_ERROR_BASE + 534L)
#define AG33250_ERROR_WRAPPED_DRIVER_ERROR                (IVIC_SPECIFIC_ERROR_BASE + 536L)
#define AG33250_ERROR_MAX_TIME_EXCEEDED                   (IVIC_SPECIFIC_ERROR_BASE + 535L)
#define AG33250_ERROR_NOT_SUPPORTED                       (IVIC_SPECIFIC_ERROR_BASE + 537L)




/**************************************************************************** 
 *---------------------------- End Include File ----------------------------* 
 ****************************************************************************/
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif // __AG33250_HEADER
