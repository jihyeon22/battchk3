#ifndef H_BATT_CHK
#define H_BATT_CHK

#define ALIVE_NOTIFIER_DEV_NUM      255
#define ALIVE_NOTIFIER_DEV_NAME     "/dev/alive"
#define MDS_DEVICE_UTIL_MAJOR_NUMBER 255

#define ALIVE_NOTIFIER_IOCTL_RESET  _IOR(ALIVE_NOTIFIER_DEV_NUM, 0, char *)
#define ALIVE_NOTIFIER_IOCTL_START  _IOR(ALIVE_NOTIFIER_DEV_NUM, 1, char *)
#define ALIVE_NOTIFIER_IOCTL_END    _IOR(ALIVE_NOTIFIER_DEV_NUM, 2, char *)

#define IOCTL_GET_ADC_RAW                _IOR(MDS_DEVICE_UTIL_MAJOR_NUMBER, 3, char *)
#define IOCTL_SET_ADC_READ_INTERVAL      _IOR(MDS_DEVICE_UTIL_MAJOR_NUMBER, 4, char *)

#define IOCTL_GET_ADC2_RAW               _IOR(MDS_DEVICE_UTIL_MAJOR_NUMBER, 5, char *)

#endif