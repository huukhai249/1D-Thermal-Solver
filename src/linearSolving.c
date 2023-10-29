#include"linearSolving.h"
/* ------------------------------------------------------------------- */
/*
   FormFunction1 - Evaluates nonlinear function, F(x).

   Input Parameters:
.  snes - the SNES context
.  x    - input vector
.  ctx  - optional user-defined context

   Output Parameter:
.  f - function vector
 */
PetscErrorCode FormFunction1(SNES snes, Vec x, Vec f, void *ctx)
{
  const PetscScalar *xx;
  PetscScalar       *ff;

  PetscFunctionBeginUser;
  /*
   Get pointers to vector data.
      - For default PETSc vectors, VecGetArray() returns a pointer to
        the data array.  Otherwise, the routine is implementation dependent.
      - You MUST call VecRestoreArray() when you no longer need access to
        the array.
   */
  PetscCall(VecGetArrayRead(x, &xx));
  PetscCall(VecGetArray(f, &ff));

  /* Compute function */
  ff[0] = xx[0] * xx[0] + xx[0] * xx[1] - 3.0;
  ff[1] = xx[0] * xx[1] + xx[1] * xx[1] - 6.0;

  /* Restore vectors */
  PetscCall(VecRestoreArrayRead(x, &xx));
  PetscCall(VecRestoreArray(f, &ff));
  PetscFunctionReturn(PETSC_SUCCESS);
}
/* ------------------------------------------------------------------- */
/*
   FormJacobian1 - Evaluates Jacobian matrix.

   Input Parameters:
.  snes - the SNES context
.  x - input vector
.  dummy - optional user-defined context (not used here)

   Output Parameters:
.  jac - Jacobian matrix
.  B - optionally different preconditioning matrix
.  flag - flag indicating matrix structure
*/
PetscErrorCode FormJacobian1(SNES snes, Vec x, Mat jac, Mat B, void *dummy)
{
  const PetscScalar *xx;
  PetscScalar        A[4];
  PetscInt           idx[2] = {0, 1};

  PetscFunctionBeginUser;
  /*
     Get pointer to vector data
  */
  PetscCall(VecGetArrayRead(x, &xx));

  /*
     Compute Jacobian entries and insert into matrix.
      - Since this is such a small problem, we set all entries for
        the matrix at once.
  */
  A[0] = 2.0 * xx[0] + xx[1];
  A[1] = xx[0];
  A[2] = xx[1];
  A[3] = xx[0] + 2.0 * xx[1];
  PetscCall(MatSetValues(B, 2, idx, 2, idx, A, INSERT_VALUES));

  /*
     Restore vector
  */
  PetscCall(VecRestoreArrayRead(x, &xx));

  /*
     Assemble matrix
  */
  PetscCall(MatAssemblyBegin(B, MAT_FINAL_ASSEMBLY));
  PetscCall(MatAssemblyEnd(B, MAT_FINAL_ASSEMBLY));
  if (jac != B) {
    PetscCall(MatAssemblyBegin(jac, MAT_FINAL_ASSEMBLY));
    PetscCall(MatAssemblyEnd(jac, MAT_FINAL_ASSEMBLY));
  }
  PetscFunctionReturn(PETSC_SUCCESS);
}

/* ------------------------------------------------------------------- */
PetscErrorCode FormFunction2(SNES snes, Vec x, Vec f, void *dummy)
{
  const PetscScalar *xx;
  PetscScalar       *ff;

  PetscFunctionBeginUser;
  /*
     Get pointers to vector data.
       - For default PETSc vectors, VecGetArray() returns a pointer to
         the data array.  Otherwise, the routine is implementation dependent.
       - You MUST call VecRestoreArray() when you no longer need access to
         the array.
  */
  PetscCall(VecGetArrayRead(x, &xx));
  PetscCall(VecGetArray(f, &ff));

  /*
     Compute function
  */
  ff[0] = PetscSinScalar(3.0 * xx[0]) + xx[0];
  ff[1] = xx[1];

  /*
     Restore vectors
  */
  PetscCall(VecRestoreArrayRead(x, &xx));
  PetscCall(VecRestoreArray(f, &ff));
  PetscFunctionReturn(PETSC_SUCCESS);
}
/* ------------------------------------------------------------------- */
PetscErrorCode FormJacobian2(SNES snes, Vec x, Mat jac, Mat B, void *dummy)
{
  const PetscScalar *xx;
  PetscScalar        A[4];
  PetscInt           idx[2] = {0, 1};

  PetscFunctionBeginUser;
  /*
     Get pointer to vector data
  */
  PetscCall(VecGetArrayRead(x, &xx));

  /*
     Compute Jacobian entries and insert into matrix.
      - Since this is such a small problem, we set all entries for
        the matrix at once.
  */
  A[0] = 3.0 * PetscCosScalar(3.0 * xx[0]) + 1.0;
  A[1] = 0.0;
  A[2] = 0.0;
  A[3] = 1.0;
  PetscCall(MatSetValues(B, 2, idx, 2, idx, A, INSERT_VALUES));

  /*
     Restore vector
  */
  PetscCall(VecRestoreArrayRead(x, &xx));

  /*
     Assemble matrix
  */
  PetscCall(MatAssemblyBegin(B, MAT_FINAL_ASSEMBLY));
  PetscCall(MatAssemblyEnd(B, MAT_FINAL_ASSEMBLY));
  if (jac != B) {
    PetscCall(MatAssemblyBegin(jac, MAT_FINAL_ASSEMBLY));
    PetscCall(MatAssemblyEnd(jac, MAT_FINAL_ASSEMBLY));
  }
  PetscFunctionReturn(PETSC_SUCCESS);
}

/*TEST

   test:
      args: -prefix_push mysolver_ -ksp_gmres_cgs_refinement_type refine_always -snes_monitor_short -prefix_pop
      requires: !single

   # test harness puts {{ }} options always at the end, need to specify the prefix explicitly
   test:
      suffix: 2
      requires: !single
      args:  -prefix_push mysolver_ -snes_monitor_short -prefix_pop -mysolver_snes_ksp_ew {{0 1}}
      output_file: output/ex1_1.out

   test:
      suffix: 3
      args: -prefix_push mysolver_ -ksp_view_solution ascii:ex1_2_sol.tmp:ascii_matlab  -snes_monitor_short -prefix_pop
      requires: !single
      output_file: output/ex1_1.out

   test:
      suffix: 4
      args: -prefix_push mysolver_ -ksp_view_solution ascii:ex1_2_sol.tmp::append  -snes_monitor_short -prefix_pop
      requires: !single
      output_file: output/ex1_1.out

   test:
      suffix: 5
      args: -prefix_push mysolver_ -ksp_view_solution ascii:ex1_2_sol.tmp:ascii_matlab:append  -snes_monitor_short -prefix_pop
      requires: !single
      output_file: output/ex1_1.out

   test:
      suffix: 6
      args: -prefix_push mysolver_ -ksp_view_solution ascii:ex1_2_sol.tmp:default:append  -snes_monitor_short -prefix_pop
      requires: !single
      output_file: output/ex1_1.out

   test:
      suffix: X
      args: -prefix_push mysolver_ -ksp_monitor_short -ksp_type gmres -ksp_gmres_krylov_monitor -snes_monitor_short -snes_rtol 1.e-4 -prefix_pop
      requires: !single x

TEST*/