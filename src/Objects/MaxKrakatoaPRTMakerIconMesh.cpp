// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0
#include "stdafx.h"

#include <boost/smart_ptr.hpp>
#include <mesh.h>

#if MAX_VERSION_MAJOR >= 25
#include <SharedMesh.h>
#endif

namespace {
// 229 vertices
float verts[] = { -0.348979f,    -0.368232f, 0.0f, -0.351557f,  -0.360916f, 0.0f, -0.355762f, -0.354866f, 0.0f,
                  -0.361505f,    -0.350008f, 0.0f, -0.367337f,  -0.34691f,  0.0f, -0.373985f, -0.344697f, 0.0f,
                  -0.381845f,    -0.343369f, 0.0f, -0.391314f,  -0.342926f, 0.0f, -0.43704f,  -0.342926f, 0.0f,
                  -0.43704f,     -0.450566f, 0.0f, -0.40932f,   -0.450566f, 0.0f, -0.40932f,  -0.415466f, 0.0f,
                  -0.392009f,    -0.415466f, 0.0f, -0.381173f,  -0.414653f, 0.0f, -0.372274f, -0.412215f, 0.0f,
                  -0.364714f,    -0.408187f, 0.0f, -0.357896f,  -0.402605f, 0.0f, -0.353733f, -0.397359f, 0.0f,
                  -0.350655f,    -0.39101f,  0.0f, -0.348754f,  -0.384028f, 0.0f, -0.34812f,  -0.376884f, 0.0f,
                  -0.377219f,    -0.381848f, 0.0f, -0.378114f,  -0.385375f, 0.0f, -0.379678f, -0.38833f,  0.0f,
                  -0.381983f,    -0.39084f,  0.0f, -0.385463f,  -0.392982f, 0.0f, -0.389685f, -0.394268f, 0.0f,
                  -0.3949f,      -0.394912f, 0.0f, -0.401363f,  -0.395126f, 0.0f, -0.40932f,  -0.395126f, 0.0f,
                  -0.40932f,     -0.363266f, 0.0f, -0.404547f,  -0.363266f, 0.0f, -0.393555f, -0.363445f, 0.0f,
                  -0.389378f,    -0.364008f, 0.0f, -0.385093f,  -0.365339f, 0.0f, -0.382038f, -0.367115f, 0.0f,
                  -0.37938f,     -0.369874f, 0.0f, -0.377535f,  -0.373437f, 0.0f, -0.37692f,  -0.377624f, 0.0f,
                  -0.268354f,    -0.379864f, 0.0f, -0.269357f,  -0.383016f, 0.0f, -0.271084f, -0.385593f, 0.0f,
                  -0.273589f,    -0.387935f, 0.0f, -0.276988f,  -0.38982f,  0.0f, -0.281109f, -0.390879f, 0.0f,
                  -0.286135f,    -0.391364f, 0.0f, -0.292247f,  -0.391526f, 0.0f, -0.30078f,  -0.391526f, 0.0f,
                  -0.30078f,     -0.362726f, 0.0f, -0.290728f,  -0.362726f, 0.0f, -0.281978f, -0.362978f, 0.0f,
                  -0.278453f,    -0.363454f, 0.0f, -0.275397f,  -0.364377f, 0.0f, -0.271944f, -0.366336f, 0.0f,
                  -0.269684f,    -0.368904f, 0.0f, -0.268436f,  -0.372064f, 0.0f, -0.26802f,  -0.375799f, 0.0f,
                  -0.260637f,    -0.404492f, 0.0f, -0.251516f,  -0.398867f, 0.0f, -0.244773f, -0.391976f, 0.0f,
                  -0.240608f,    -0.38335f,  0.0f, -0.23922f,   -0.372517f, 0.0f, -0.240117f, -0.364567f, 0.0f,
                  -0.242807f,    -0.358083f, 0.0f, -0.247019f,  -0.352865f, 0.0f, -0.252481f, -0.348714f, 0.0f,
                  -0.258714f,    -0.34573f,  0.0f, -0.265381f,  -0.344012f, 0.0f, -0.272935f, -0.343198f, 0.0f,
                  -0.281832f,    -0.342926f, 0.0f, -0.3285f,    -0.342926f, 0.0f, -0.3285f,   -0.450566f, 0.0f,
                  -0.30078f,     -0.450566f, 0.0f, -0.30078f,   -0.411146f, 0.0f, -0.288f,    -0.411146f, 0.0f,
                  -0.258674f,    -0.450566f, 0.0f, -0.22464f,   -0.450566f, 0.0f, -0.12834f,  -0.342926f, 0.0f,
                  -0.22338f,     -0.342926f, 0.0f, -0.22338f,   -0.363806f, 0.0f, -0.18972f,  -0.363806f, 0.0f,
                  -0.18972f,     -0.450566f, 0.0f, -0.162f,     -0.450566f, 0.0f, -0.162f,    -0.363806f, 0.0f,
                  -0.12834f,     -0.363806f, 0.0f, 0.05544f,    -0.342926f, 0.0f, 0.0231104f, -0.342926f, 0.0f,
                  -0.000953406f, -0.396876f, 0.0f, -0.0250875f, -0.342926f, 0.0f, -0.0576f,   -0.342926f, 0.0f,
                  -0.0576f,      -0.450566f, 0.0f, -0.03114f,   -0.450566f, 0.0f, -0.03114f,  -0.378459f, 0.0f,
                  -0.0112556f,   -0.425186f, 0.0f, 0.00783566f, -0.425186f, 0.0f, 0.02772f,   -0.378459f, 0.0f,
                  0.02772f,      -0.450566f, 0.0f, 0.05544f,    -0.450566f, 0.0f, 0.127396f,  -0.431655f, 0.0f,
                  0.123625f,     -0.433497f, 0.0f, 0.119636f,   -0.434689f, 0.0f, 0.115701f,  -0.435086f, 0.0f,
                  0.111432f,     -0.434915f, 0.0f, 0.108465f,   -0.4344f,   0.0f, 0.106312f,  -0.433524f, 0.0f,
                  0.104484f,     -0.432268f, 0.0f, 0.103074f,   -0.430789f, 0.0f, 0.102315f,  -0.429236f, 0.0f,
                  0.101989f,     -0.427412f, 0.0f, 0.10188f,    -0.425119f, 0.0f, 0.102396f,  -0.421661f, 0.0f,
                  0.103943f,     -0.418944f, 0.0f, 0.106467f,   -0.416876f, 0.0f, 0.109913f,  -0.415368f, 0.0f,
                  0.113838f,     -0.414419f, 0.0f, 0.119247f,   -0.413597f, 0.0f, 0.13068f,   -0.412406f, 0.0f,
                  0.13068f,      -0.429307f, 0.0f, 0.13068f,    -0.450566f, 0.0f, 0.15642f,   -0.450566f, 0.0f,
                  0.15642f,      -0.395202f, 0.0f, 0.153952f,   -0.382511f, 0.0f, 0.146548f,  -0.373715f, 0.0f,
                  0.133594f,     -0.368578f, 0.0f, 0.114477f,   -0.366866f, 0.0f, 0.105157f,  -0.367233f, 0.0f,
                  0.0958556f,    -0.368333f, 0.0f, 0.0878555f,  -0.369702f, 0.0f, 0.08244f,   -0.370874f, 0.0f,
                  0.08244f,      -0.390266f, 0.0f, 0.0848307f,  -0.390266f, 0.0f, 0.0953325f, -0.386774f, 0.0f,
                  0.102431f,     -0.385073f, 0.0f, 0.109094f,   -0.384506f, 0.0f, 0.118511f,  -0.385164f, 0.0f,
                  0.125319f,     -0.387137f, 0.0f, 0.129447f,   -0.390834f, 0.0f, 0.130823f,  -0.396662f, 0.0f,
                  0.130823f,     -0.397106f, 0.0f, 0.119522f,   -0.397939f, 0.0f, 0.108619f,  -0.399134f, 0.0f,
                  0.098782f,     -0.40098f,  0.0f, 0.0906806f,  -0.403769f, 0.0f, 0.084208f,  -0.407626f, 0.0f,
                  0.0793983f,    -0.412678f, 0.0f, 0.0764146f,  -0.419141f, 0.0f, 0.07542f,   -0.427234f, 0.0f,
                  0.0773729f,    -0.43739f,  0.0f, 0.0832317f,  -0.445556f, 0.0f, 0.0919839f, -0.450934f, 0.0f,
                  0.102617f,     -0.452726f, 0.0f, 0.107335f,   -0.452519f, 0.0f, 0.111656f,  -0.451898f, 0.0f,
                  0.115707f,     -0.450844f, 0.0f, 0.119613f,   -0.449337f, 0.0f, 0.122453f,  -0.4478f,   0.0f,
                  0.125473f,     -0.445792f, 0.0f, 0.13068f,    -0.441957f, 0.0f, 0.235291f,  -0.404374f, 0.0f,
                  0.26442f,      -0.369386f, 0.0f, 0.234203f,   -0.369386f, 0.0f, 0.20646f,   -0.404964f, 0.0f,
                  0.20646f,      -0.338066f, 0.0f, 0.18036f,    -0.338066f, 0.0f, 0.18036f,   -0.450566f, 0.0f,
                  0.20646f,      -0.450566f, 0.0f, 0.20646f,    -0.423966f, 0.0f, 0.213556f,  -0.415219f, 0.0f,
                  0.236363f,     -0.450566f, 0.0f, 0.26658f,    -0.450566f, 0.0f, 0.35982f,   -0.405648f, 0.0f,
                  0.357322f,     -0.389065f, 0.0f, 0.349826f,   -0.376869f, 0.0f, 0.337369f,  -0.369367f, 0.0f,
                  0.319987f,     -0.366866f, 0.0f, 0.300767f,   -0.369802f, 0.0f, 0.286128f,  -0.378611f, 0.0f,
                  0.276867f,     -0.392442f, 0.0f, 0.27378f,    -0.410446f, 0.0f, 0.277042f,  -0.428424f, 0.0f,
                  0.286829f,     -0.441741f, 0.0f, 0.302741f,   -0.44998f,  0.0f, 0.32438f,   -0.452726f, 0.0f,
                  0.33346f,      -0.452327f, 0.0f, 0.341706f,   -0.45113f,  0.0f, 0.349789f,  -0.449044f, 0.0f,
                  0.35838f,      -0.445979f, 0.0f, 0.35838f,    -0.425006f, 0.0f, 0.355466f,  -0.425006f, 0.0f,
                  0.35013f,      -0.428371f, 0.0f, 0.343155f,   -0.431514f, 0.0f, 0.335232f,  -0.433788f, 0.0f,
                  0.327054f,     -0.434546f, 0.0f, 0.315534f,   -0.433272f, 0.0f, 0.307201f,  -0.42945f,  0.0f,
                  0.302001f,     -0.423226f, 0.0f, 0.29988f,    -0.414746f, 0.0f, 0.35982f,   -0.414746f, 0.0f,
                  0.299807f,     -0.399446f, 0.0f, 0.30146f,    -0.392032f, 0.0f, 0.305253f,  -0.386963f, 0.0f,
                  0.31079f,      -0.38404f,  0.0f, 0.317672f,   -0.383066f, 0.0f, 0.324734f,  -0.384095f, 0.0f,
                  0.329655f,     -0.387179f, 0.0f, 0.332595f,   -0.392303f, 0.0f, 0.33372f,   -0.399446f, 0.0f,
                  0.43704f,      -0.369316f, 0.0f, 0.435633f,   -0.369188f, 0.0f, 0.43401f,   -0.369098f, 0.0f,
                  0.430906f,     -0.369026f, 0.0f, 0.425315f,   -0.369641f, 0.0f, 0.419217f,  -0.371484f, 0.0f,
                  0.412308f,     -0.375172f, 0.0f, 0.40428f,    -0.38132f,  0.0f, 0.40428f,   -0.369386f, 0.0f,
                  0.37818f,      -0.369386f, 0.0f, 0.37818f,    -0.450566f, 0.0f, 0.40428f,   -0.450566f, 0.0f,
                  0.40428f,      -0.39615f,  0.0f, 0.409025f,   -0.394667f, 0.0f, 0.413445f,  -0.39369f,  0.0f,
                  0.418027f,     -0.393147f, 0.0f, 0.423259f,   -0.392966f, 0.0f, 0.426018f,  -0.393034f, 0.0f,
                  0.429391f,     -0.393236f, 0.0f, 0.432566f,   -0.393574f, 0.0f, 0.434731f,  -0.394046f, 0.0f,
                  0.43704f,      -0.394046f, 0.0f };

// 221 faces
int faces[] = { 21,  22,  1,   1, 1, 38,  21,  1,   1, 1, 37,  38,  1,   1, 1, 0,   1,   22,  1, 1, 20,  0,   22,  1, 1,
                19,  20,  22,  1, 1, 18,  19,  22,  1, 1, 17,  18,  22,  1, 1, 16,  17,  22,  1, 1, 16,  22,  23,  1, 2,
                15,  16,  23,  1, 1, 15,  23,  24,  1, 2, 14,  15,  24,  1, 1, 13,  14,  24,  1, 1, 13,  24,  25,  1, 2,
                37,  1,   2,   1, 2, 36,  37,  2,   1, 1, 36,  2,   3,   1, 2, 36,  3,   4,   1, 2, 35,  36,  4,   1, 1,
                35,  4,   5,   1, 2, 34,  35,  5,   1, 1, 34,  5,   6,   1, 2, 33,  34,  6,   1, 1, 33,  6,   7,   1, 2,
                32,  33,  7,   1, 1, 12,  13,  25,  1, 1, 12,  25,  26,  1, 2, 12,  26,  27,  1, 2, 11,  12,  27,  1, 1,
                11,  27,  28,  1, 2, 11,  28,  29,  1, 2, 32,  7,   8,   1, 2, 31,  32,  8,   1, 1, 30,  31,  8,   1, 1,
                30,  8,   9,   1, 2, 29,  30,  9,   1, 1, 11,  29,  9,   1, 0, 10,  11,  9,   1, 5, 75,  76,  57,  1, 3,
                74,  75,  57,  1, 1, 57,  40,  41,  1, 2, 74,  57,  41,  1, 0, 74,  41,  42,  1, 2, 74,  42,  43,  1, 2,
                74,  43,  44,  1, 2, 74,  44,  45,  1, 2, 40,  57,  58,  1, 2, 74,  45,  46,  1, 2, 73,  74,  46,  1, 1,
                73,  46,  47,  1, 2, 71,  72,  73,  1, 3, 70,  71,  73,  1, 1, 70,  73,  47,  1, 0, 70,  47,  48,  1, 2,
                69,  70,  48,  1, 1, 69,  48,  49,  1, 2, 69,  49,  50,  1, 2, 68,  69,  50,  1, 1, 68,  50,  51,  1, 2,
                68,  51,  52,  1, 2, 67,  68,  52,  1, 1, 40,  58,  59,  1, 2, 39,  40,  59,  1, 1, 39,  59,  60,  1, 2,
                39,  60,  61,  1, 2, 56,  39,  61,  1, 1, 55,  56,  61,  1, 1, 55,  61,  62,  1, 2, 55,  62,  63,  1, 2,
                55,  63,  64,  1, 2, 54,  55,  64,  1, 1, 54,  64,  65,  1, 2, 54,  65,  66,  1, 2, 53,  54,  66,  1, 1,
                53,  66,  67,  1, 2, 53,  67,  52,  1, 4, 83,  84,  77,  1, 3, 83,  77,  78,  1, 2, 81,  82,  83,  1, 3,
                80,  81,  83,  1, 1, 80,  83,  78,  1, 0, 79,  80,  78,  1, 5, 96,  97,  85,  1, 3, 95,  96,  85,  1, 1,
                95,  85,  86,  1, 2, 95,  86,  87,  1, 2, 94,  95,  87,  1, 1, 93,  94,  87,  1, 1, 92,  93,  87,  1, 1,
                92,  87,  88,  1, 2, 92,  88,  89,  1, 2, 92,  89,  90,  1, 2, 91,  92,  90,  1, 5, 98,  99,  119, 1, 1,
                117, 98,  119, 1, 1, 117, 119, 120, 1, 2, 116, 117, 120, 1, 1, 128, 129, 130, 1, 3, 128, 130, 131, 1, 2,
                127, 128, 131, 1, 1, 126, 127, 131, 1, 1, 126, 131, 132, 1, 2, 125, 126, 132, 1, 1, 125, 132, 133, 1, 2,
                124, 125, 133, 1, 1, 124, 133, 134, 1, 2, 123, 124, 134, 1, 1, 123, 134, 135, 1, 2, 157, 118, 119, 1, 3,
                157, 119, 99,  1, 0, 156, 157, 99,  1, 1, 156, 99,  100, 1, 2, 122, 123, 135, 1, 1, 122, 135, 136, 1, 2,
                121, 122, 136, 1, 1, 120, 121, 136, 1, 1, 120, 136, 137, 1, 2, 120, 137, 138, 1, 2, 116, 120, 138, 1, 0,
                116, 138, 139, 1, 2, 115, 116, 139, 1, 1, 115, 139, 140, 1, 2, 114, 115, 140, 1, 1, 113, 114, 140, 1, 1,
                113, 140, 141, 1, 2, 112, 113, 141, 1, 1, 155, 156, 100, 1, 1, 155, 100, 101, 1, 2, 154, 155, 101, 1, 1,
                153, 154, 101, 1, 1, 153, 101, 102, 1, 2, 152, 153, 102, 1, 1, 112, 141, 142, 1, 2, 111, 112, 142, 1, 1,
                151, 152, 102, 1, 1, 151, 102, 103, 1, 2, 150, 151, 103, 1, 1, 150, 103, 104, 1, 2, 149, 150, 104, 1, 1,
                149, 104, 105, 1, 2, 148, 149, 105, 1, 1, 148, 105, 106, 1, 2, 147, 148, 106, 1, 1, 147, 106, 107, 1, 2,
                146, 147, 107, 1, 1, 146, 107, 108, 1, 2, 145, 146, 108, 1, 1, 145, 108, 109, 1, 2, 144, 145, 109, 1, 1,
                144, 109, 110, 1, 2, 143, 144, 110, 1, 1, 142, 143, 110, 1, 1, 111, 142, 110, 1, 4, 158, 159, 160, 1, 3,
                158, 160, 161, 1, 2, 168, 169, 158, 1, 3, 167, 168, 158, 1, 1, 167, 158, 161, 1, 0, 164, 165, 166, 1, 3,
                163, 164, 166, 1, 1, 161, 162, 163, 1, 3, 161, 163, 166, 1, 0, 167, 161, 166, 1, 4, 206, 198, 170, 1, 1,
                206, 170, 171, 1, 2, 205, 206, 171, 1, 1, 205, 171, 172, 1, 2, 205, 172, 173, 1, 2, 204, 205, 173, 1, 1,
                204, 173, 174, 1, 2, 203, 204, 174, 1, 1, 202, 203, 174, 1, 1, 202, 174, 175, 1, 2, 201, 202, 175, 1, 1,
                200, 201, 175, 1, 1, 200, 175, 176, 1, 2, 199, 200, 176, 1, 1, 199, 176, 177, 1, 2, 198, 199, 177, 1, 1,
                198, 177, 178, 1, 2, 196, 197, 170, 1, 3, 196, 170, 198, 1, 0, 196, 198, 178, 1, 0, 196, 178, 179, 1, 2,
                195, 196, 179, 1, 1, 195, 179, 180, 1, 2, 195, 180, 181, 1, 2, 194, 195, 181, 1, 1, 193, 194, 181, 1, 1,
                193, 181, 182, 1, 2, 192, 193, 182, 1, 1, 192, 182, 183, 1, 2, 191, 192, 183, 1, 1, 191, 183, 184, 1, 2,
                190, 191, 184, 1, 1, 190, 184, 185, 1, 2, 186, 187, 188, 1, 3, 186, 188, 189, 1, 2, 185, 186, 189, 1, 1,
                190, 185, 189, 1, 4, 227, 228, 207, 1, 3, 226, 227, 207, 1, 1, 226, 207, 208, 1, 2, 226, 208, 209, 1, 2,
                225, 226, 209, 1, 1, 225, 209, 210, 1, 2, 225, 210, 211, 1, 2, 224, 225, 211, 1, 1, 224, 211, 212, 1, 2,
                223, 224, 212, 1, 1, 223, 212, 213, 1, 2, 222, 223, 213, 1, 1, 222, 213, 214, 1, 2, 221, 222, 214, 1, 1,
                220, 221, 214, 1, 1, 219, 220, 214, 1, 1, 217, 218, 219, 1, 3, 216, 217, 219, 1, 1, 216, 219, 214, 1, 0,
                215, 216, 214, 1, 5 };
#if MAX_VERSION_MAJOR >= 25
MaxSDK::SharedMeshPtr g_globalMesh;
#else
Mesh g_globalMesh;
#endif
} // namespace

namespace krakatoa {
namespace max3d {

extern void build_icon_mesh( Mesh& outMesh, float verts[], int faces[], int vertCount, int faceCount );

}
} // namespace krakatoa

#if MAX_VERSION_MAJOR >= 25

static void InitializeIconMesh() {

    if( !g_globalMesh ) {
        g_globalMesh = new MaxSDK::SharedMesh();
        int vertCount = sizeof( verts ) / sizeof( verts[0] ) / 3;
        int faceCount = sizeof( faces ) / sizeof( faces[0] ) / 5;

        krakatoa::max3d::build_icon_mesh( g_globalMesh->GetMesh(), verts, faces, vertCount, faceCount );

        g_globalMesh->GetMesh().buildBoundingBox();
    }
}

Mesh* GetPRTMakerIconMesh() {
    InitializeIconMesh();
    return g_globalMesh->GetMeshPtr();
}

MaxSDK::SharedMeshPtr GetPRTMakerIconMeshShared() {
    InitializeIconMesh();
    return g_globalMesh;
}

#else

Mesh* GetPRTMakerIconMesh() {
    if( g_globalMesh.getNumVerts() == 0 ) {
        int vertCount = sizeof( verts ) / sizeof( verts[0] ) / 3;
        int faceCount = sizeof( faces ) / sizeof( faces[0] ) / 5;

        krakatoa::max3d::build_icon_mesh( g_globalMesh, verts, faces, vertCount, faceCount );

        g_globalMesh.buildBoundingBox();
    }

    return &g_globalMesh;
}

#endif