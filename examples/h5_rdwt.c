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
 *  This example illustrates how to write and read data in an existing
 *  dataset.  It is used in the HDF5 Tutorial.
 */

#include "hdf5.h"
#define FILE "/home/" USERNAME "/dset.h5"

#define URL      "http://127.0.0.1:5101"
#define USERNAME "test_user1"
#define PASSWORD "test"

int main() {

   hid_t       file_id, dataset_id, fapl;  /* identifiers */
   herr_t      status;
   int         i, j, dset_data[4][6];

   /* Initialize REST VOL plugin access */
   RVinit();

   /* Associate the REST VOL plugin with a FAPL and register
    * it with the library
    */
   fapl = H5Pcreate(H5P_FILE_ACCESS);
   H5Pset_fapl_rest_vol(fapl, URL, USERNAME, PASSWORD);

   /* Initialize the dataset. */
   for (i = 0; i < 4; i++)
      for (j = 0; j < 6; j++)
         dset_data[i][j] = i * 6 + j + 1;

   /* Open an existing file. */
   file_id = H5Fopen(FILE, H5F_ACC_RDWR, fapl);

   /* Open an existing dataset. */
   dataset_id = H5Dopen2(file_id, "/dset", H5P_DEFAULT);

   /* Write the dataset. */
   status = H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                     dset_data);

   status = H5Dread(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                    dset_data);

   /* Close the dataset. */
   status = H5Dclose(dataset_id);

   /* Close the File Access Property List */
   status = H5Pclose(fapl);

   /* Close the file. */
   status = H5Fclose(file_id);

   /* Terminate REST VOL plugin access */
   status = RVterm();
}
