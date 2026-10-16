#include <string.h>

char *strerror(int error_number)
{
	switch (error_number)
	{
		case 0:
			return "Success";
		case 1:
			return "Not super-user";
		case 2:
			return "No such file or directory";
		case 3:
			return "No such process";
		case 4:
			return "Interrupted system call";
		case 5:
			return "I/O error";
		case 6:
			return "No such device or address";
		case 7:
			return "Arg list too long";
		case 8:
			return "Exec format error";
		case 9:
			return "Bad file number";
		case 10:
			return "No children";
		case 11:
			return "No more processes";
		case 12:
			return "Not enough core";
		case 13:
			return "Permission denied";
		case 14:
			return "Bad address";
		case 15:
			return "Block device required";
		case 16:
			return "Mount device busy";
		case 17:
			return "File exists";
		case 18:
			return "Cross-device link";
		case 19:
			return "No such device";
		case 20:
			return "Not a directory";
		case 21:
			return "Is a directory";
		case 22:
			return "Invalid argument";
		case 23:
			return "Too many open files in system";
		case 24:
			return "Too many open files";
		case 25:
			return "Not a typewriter";
		case 26:
			return "Text file busy";
		case 27:
			return "File too large";
		case 28:
			return "No space left on device";
		case 29:
			return "Illegal seek";
		case 30:
			return "Read only file system";
		case 31:
			return "Too many links";
		case 32:
			return "Broken pipe";
		case 33:
			return "Math arg out of domain of func";
		case 34:
			return "Math result not representable";
		case 35:
			return "No message of desired type";
		case 36:
			return "Identifier removed";
		case 37:
			return "Channel number out of range";
		case 38:
			return "Level 2 not synchronized";
		case 39:
			return "Level 3 halted";
		case 40:
			return "Level 3 reset";
		case 41:
			return "Link number out of range";
		case 42:
			return "Protocol driver not attached";
		case 43:
			return "No CSI structure available";
		case 44:
			return "Level 2 halted";
		case 45:
			return "Deadlock condition";
		case 46:
			return "No record locks available";
		case 50:
			return "Invalid exchange";
		case 51:
			return "Invalid request descriptor";
		case 52:
			return "Exchange full";
		case 53:
			return "No anode";
		case 54:
			return "Invalid request code";
		case 55:
			return "Invalid slot";
		case 56:
			return "File locking deadlock error";
		case 57:
			return "Bad font file fmt";
		case 60:
			return "Device not a stream";
		case 61:
			return "No data (for no delay io)";
		case 62:
			return "Timer expired";
		case 63:
			return "Out of streams resources";
		case 64:
			return "Machine is not on the network";
		case 65:
			return "Package not installed";
		case 66:
			return "The object is remote";
		case 67:
			return "The link has been severed";
		case 68:
			return "Advertise error";
		case 69:
			return "Srmount error";
		case 70:
			return "Communication error on send";
		case 71:
			return "Protocol error";
		case 74:
			return "Multihop attempted";
		case 75:
			return "Inode is remote (not really error)";
		case 76:
			return "Cross mount point (not really error)";
		case 77:
			return "Trying to read unreadable message";
		case 79:
			return "Inappropriate file type or format";
		case 80:
			return "Given log. name not unique";
		case 81:
			return "f.d. invalid for this operation";
		case 82:
			return "Remote address changed";
		case 83:
			return "Can't access a needed shared lib";
		case 84:
			return "Accessing a corrupted shared lib";
		case 85:
			return ".lib section in a.out corrupted";
		case 86:
			return "Attempting to link in too many libs";
		case 87:
			return "Attempting to exec a shared library";
		case 88:
			return "Function not implemented";
		case 90:
			return "Directory not empty";
		case 91:
			return "File or path name too long";
		case 92:
			return "Too many symbolic links";
		case 95:
			return "Operation not supported on transport endpoint";
		case 96:
			return "Protocol family not supported";
		case 104:
			return "Connection reset by peer";
		case 105:
			return "No buffer space available";
		case 106:
			return "Address family not supported by protocol family";
		case 107:
			return "Protocol wrong type for socket";
		case 108:
			return "Socket operation on non-socket";
		case 109:
			return "Protocol not available";
		case 110:
			return "Can't send after socket shutdown";
		case 111:
			return "Connection refused";
		case 112:
			return "Address already in use";
		case 113:
			return "Connection aborted";
		case 114:
			return "Network is unreachable";
		case 115:
			return "Network interface is not configured";
		case 116:
			return "Connection timed out";
		case 117:
			return "Host is down";
		case 118:
			return "Host is unreachable";
		case 119:
			return "Connection already in progress";
		case 120:
			return "Socket already connected";
		case 121:
			return "Destination address required";
		case 122:
			return "Message too long";
		case 123:
			return "Unknown protocol";
		case 124:
			return "Socket type not supported";
		case 125:
			return "Address not available";
		case 127:
			return "Socket is already connected";
		case 128:
			return "Socket is not connected";
		case 134:
			return "Not supported";
		case 135:
			return "No medium (in tape drive)";
		case 139:
			return "Value too large for defined data type";
		case 140:
			return "Operation canceled";
		case 141:
			return "State not recoverable";
		case 142:
			return "Previous owner died";
		case 143:
			return "Streams pipe error";
		default:
			return "Unknown error";
	}
}

