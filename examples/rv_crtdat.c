/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the files COPYING and Copyright.html.  COPYING can be found at the root   *
 * of the source code distribution tree; Copyright.html can be found at the  *
 * root level of an installed copy of the electronic HDF5 document set and   *
 * is linked from the top-level documents page.  It can also be found at     *
 * http://hdfgroup.org/HDF5/doc/Copyright.html.  If you do not have          *
 * access to either file, you may request a copy from help@hdfgroup.org.     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 *  This example illustrates how to create a dataset that is a 4 x 6 
 *  array.  It is used in the HDF5 Tutorial.
 */

#include <stdlib.h>

#include "hdf5.h"
#include "rest_vol_public.h"

#define FILE "dset.h5"
#define FILE_NAME_MAX_LENGTH 256

int main() {

   hid_t       file_id, fapl_id, dataset_id, dataspace_id;  /* identifiers */
   hsize_t     dims[2];
   const char *username;
   char        filename[FILE_NAME_MAX_LENGTH];
   herr_t      status;

   RVinit();

   fapl_id = H5Pcreate(H5P_FILE_ACCESS);
   H5Pset_fapl_rest_vol(fapl_id);

   username = getenv("HSDS_USERNAME");

   snprintf(filename, FILE_NAME_MAX_LENGTH, "/home/%s/" FILE, username);

   /* Create a new file using default properties. */
   file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, fapl_id);

   /* Create the data space for the dataset. */
   dims[0] = 4; 
   dims[1] = 6; 
   dataspace_id = H5Screate_simple(2, dims, NULL);

   /* Create the dataset. */
   dataset_id = H5Dcreate2(file_id, "/dset", H5T_STD_I32BE, dataspace_id, 
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

   /* End access to the dataset and release resources used by it. */
   status = H5Dclose(dataset_id);

   /* Terminate access to the data space. */ 
   status = H5Sclose(dataspace_id);

   status = H5Pclose(fapl_id);

   /* Close the file. */
   status = H5Fclose(file_id);

   RVterm();
}

