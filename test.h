/*
 *  test.h
 *  integer-fhe
 *
 *  Created by Henning Perl on 17.12.10.
 *
 */

#pragma once
#ifndef TEST_H
#define TEST_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "integer-fhe.h"

#define RUNS 10
#define KEYRUNS 5

void test_encryt_decrypt();

void test_halfadd();

void test_fulladd();

void test_recrypt();

void test_homomorphic();

void test_suite();

#endif