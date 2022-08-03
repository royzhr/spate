/*
 *  Rodzhang
 *
 * This file is used for export's dependence.
 */

#ifndef __SPATE_EXPORT_NEED_H__
#define __SPATE_EXPORT_NEED_H__




#define __ntohl ntohl
#define __htonl htonl
#define __htons htons
#define __ntohs ntohs


#ifndef __inline
# define __inline inline __attribute__((always_inline))
#endif



#endif /* __SPATE_EXPORT_NEED_H__ */
