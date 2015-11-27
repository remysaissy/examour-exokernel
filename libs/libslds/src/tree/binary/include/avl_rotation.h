/*
 * avl_rotation.h
 *
 *  Created on: 5 déc. 2008
 *      Author: remy
 */

#ifndef AVL_ROTATION_H_
#define AVL_ROTATION_H_

/**
 * This header contains declaration for avl rotations in the libslds.
 */

void    *avl_single_rotate_with_left(void *node,
                                     unsigned int m);

void    *avl_single_rotate_with_right(void *node,
                                     unsigned int m);


void    *avl_parent_rotate_with_left(void *node,
                                     unsigned int m);

void    *avl_parent_rotate_with_right(void *node,
                                     unsigned int m);



#endif /* AVL_ROTATION_H_ */
