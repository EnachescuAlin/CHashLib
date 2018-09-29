#include "md2.h"
#include <stdio.h>
#include <string.h>

#include "linux_color.h"
#include "util.h"

static const char* expectedHash[] = {
    "8350e5a3e24c153df2275c9f80692773",
    "32ec01ec4a6dac72c0ab96fb34c0b5d1",
    "2909579e435315f8ca9b3fb77f373de3",
    "28536cbf65c9dd94e9e7d750367cc448",
    "964f45b9af73ed6fdf8d897312de1aca",
    "0ff4277b4f6d46a3d7839a3756a3966a",
    "4ae2e44f067f215a482f42bd69a32213",
    "dcc285be324e660da6fe784a157a188e",
    "da1057cf0549cb2d9e39ef5b49ca22e6",
    "b41a30cc233cacf95cdeff9ff52df06d",
    "ede40c056c099b6c6534bcb5ddf6a85e",
    "4c9699585d4a055ac540fea3d75ca1de",
    "43ee8563f0a8785a5406554db79e8dbc",
    "cc42b2fb09dd33908dc6dd2b757d0735",
    "e0d19f66f8db7e46196ba529ae7918d2",
    "a1379a1027d0d29af98200799b8d5d8e",
    "b437ae50feb09a37c16b4c605cd642da",
    "dbf15a5fdfd6f7e9ece27d5e310c58ed",
    "35c66e04600e34abb8e917f51958d0e9",
    "292d70d949fe66f5a7bba501bca8e52c",
    "8e84726137459c53984f23e1aa8555a8",
    "a26fe611acddede12a4008df696a6cd4",
    "47f68ecbbaf0b31f8bffb86e42071c54",
    "3912c37b249c0dd44efb94253c7fa9ba",
    "e0711473eca660b11dcd67fd3741585c",
    "2f922b6a4b74596c38d9f8e3be6c0af7",
    "c4fb39e77e9d6fcd4895ebba0b066792",
    "134d6fed9361431f14e878b38812a370",
    "f294feeceb9a922453102366f36779ff",
    "5fec3b677fb0adc925c625e8da5414ac",
    "f0e0980b116284a98b6ee53ed17c1dfb",
    "01698e8da7308690dc88f711443280d5",
    "fc6f34c6b52617387390d85ea9e510be",
    "b4ee16ace7dc51aef575bd1de6078113",
    "076c99d0a0e79c62f55c6b2dc91c9cc7",
    "f77788ca1c67bb7512fd76b087257344",
    "d6cd63153bf74113e5099a00f97f8fce",
    "70ab9b09116b92239b19dac7c155a83d",
    "2ac82d20388f472620bc35a05aadd86b",
    "a68c384e63a8a96baf7be42485e4e88b",
    "8f38ed3a8715c7d432aab358de76c42b",
    "797f66c76440c06ae2602144d7d3f346",
    "2b4e98f7542c7625f9b563fb39f4371d",
    "ff298d61dbabda8d56a1de62c09268f2",
    "569e4823ebf6d987e7687fd83551b373",
    "98ca02738a89fa2958d07c11660e058c",
    "3daaa18521aae494094b1b5f1957fe00",
    "9a8949c53f771387ea01946f580bd322",
    "4b5d4668829a8cd547df0af91c016757",
    "ff2b73357083bc4861c8a2e6fe1261f7",
    "66bcdf217a2b653c3a7ae6be455dda4b",
    "34bb0b16f9b6425e306901ff2fa621c4",
    "53620796c2d21df800840eb622c6c2c4",
    "00f79ca527493cc867c2ebf920be9657",
    "056b766f30aa51ccf5319be4231d7f94",
    "a986ba1188b499e93ccc132cd98baac6",
    "6e1197b18716e5fcfe53323fc4cc9049",
    "b9f65bebb39f7c72a7b03952794c0de3",
    "e8299f82cf0b4e0b633b337444570251",
    "14fb2472a5072da52c6abfb99810e441",
    "1373107e8991b1f8b92ebf0c053576b3",
    "6cb663a0137ad4da7f6baa67ea114013",
    "3754f91215038cc166751f83dc412afe",
    "1a6609e5ad77de912412398113137b6f",
    "14db72af1a6b6290199f6be37fd78339",
    "76bbcab8565ae819f4568595ed3678bc",
    "1b015f30d064dd37df945c8db508c5ab",
    "ec215d8b89dcc27c2ae6e0c944066c8a",
    "8721bbddec355d70c0705c19f04961fc",
    "56845255958ef2163433ea15ba3d3322",
    "eb41810521bec994c33402bb4d73bc4b",
    "111e6ca0f6d82d40642a08b1b4d51b6c",
    "7553c8ef23929cd9e54ae472081a7727",
    "7d5265237dc7f481ca6ddcbf89251f2f",
    "d47538b3467d1acc1ef5abd7cd3b9188",
    "0d76f8bdd70c0da25e15e24e6a41201e",
    "bee7e4824c95ded04dedf0f1ec2b07bc",
    "082ee77f8cbb461e8c2d1ed0aa948180",
    "2c072dc03fc3b2ca3fdcf7f53fbf1a5e",
    "502de2ab8a605b06bd14b1ce15669a4c",
    "4cc78ffb28becdba6093dfea8a0e6371",
    "1e463b340a1c1932fad38c5a8d885d9d",
    "07397c21fe78195356f45f7c6efaa038",
    "ba0c6f2cbd4f73de6af37a12788e666a",
    "0f08ea88aa6833f5cfb7e2322a308de5",
    "b6d4d9bb0ecbe564691c8a6b2b352669",
    "5806921a6780ec2ad9e385ecb72b235c",
    "ba75790d9baa89dda63c385770b77c09",
    "f4e170074d3bfb7191db91dfd5011c97",
    "5dfebaa6789869287b87621b603487f3",
    "6724d151cb87ea488fc95fd3b2df1510",
    "b7c1b524f8a3082378bc2ff93818af93",
    "5f6fe73fce5f8e8d3d570efe6f045962",
    "6a77f1936a7eba4a3e824128b1b70f8d",
    "6e32440e1c5d55e5440ced359f2763cc",
    "ce00743f7a276bbf322a9637caa345d6",
    "8d89666a0ae3064b15b7fd3fedfddff6",
    "75b55d023223879acfc8c3db5e68c42a",
    "8cd37790104b96a576cf586f904f8c31",
    "080c91a3e4c737b72045a42a982273e6",
    "0ee8f251cfd5407b7ee13353e0746eb2",
    "2a30f5c32ef56593d387dcbaacde83e4",
    "b23716d3c4f3629628a2910b7c67c14a",
    "282c3419e49133a14587c7b199be60a0",
    "3e579c7e885e6f5d67219be37fa9053e",
    "f02d2fd4cc5afc5aea6daabb106d4d41",
    "9acbb544d0b1c7501f73404c5e71f55e",
    "5ecda7919ee5501d424b41532c54050c",
    "8df27fcea9ec9035864e4c3787c2ecaa",
    "4b791d012589464d14e6d9eee9f8ff6b",
    "1ede540867a90a6d5aa5ef8ae465abb7",
    "7a6019c930fcf3d72da9427ea0dbeb62",
    "897047208f5ec1c8fdf218ec6460d3a8",
    "1f74137053f14cb959fbec201ca9d7df",
    "bb07d286a65b583e7df4565c603a42d7",
    "e446d0450c047e980222ac709d290a3d",
    "0fe20f19c59b7640937672feebacc249",
    "f32c26744604d2b1506687f639eb8bc0",
    "7de18f7b17c46467301691ae391e34b0",
    "12fbc29dc0c3a0a984e6fb41e4da2d0b",
    "fac6b72400ffaa4762e9395e2e73fd6e",
    "f056a11a5addd136cac27b25020d86ce",
    "bb5bac5dcb517e183f1b7722c2dd7822",
    "9238676d8672421b498cdea10e08f5b6",
    "c1f5214279b0e09b3e911c6f0d76ff09",
    "86e0b013444809c59ae68364bb68f66b",
    "33c237dc38de11a77da5d115154458ff",
    "da0e0c1ae3a8bb8c272259990c1fd8a7",
    "f9d03ed17e9bdd191cd8a5c46c1d1e03",
    "84e60becc36c6bb316292b824d7d5287",
    "e557c8627c2ff9f1f2a33958bcfcc383",
    "575fb4c94556d22c2bd21ceab748fb83",
    "721627ea75b997631cf096a33026c31f",
    "a34fafa251ad08d979fb42ca21e8607e",
    "4946f5ce80bb11dcf7143e3fd4288c5e",
    "f69a4f91ce2ba4fdb1e82de6a4b8085f",
    "bee0868a97442584d5d8a333752d9fc8",
    "b33432f4b4bf5a6c8c5b9ba515318268",
    "6460a2219ed4ca690fbbc38186f2c289",
    "92d8561fb0fc2e12e4bbbcb427ce9c3a",
    "e0bbf1547f41563bad08c91f7bea277a",
    "5ae2b53a84a2f3ee894beee9ac01d190",
    "e49f9b7050272697e4ae3239b5db9755",
    "9ff60e8cfa5f4807de4455d017bf2862",
    "b54cd369f6668b67da8076f27055d548",
    "c3415512169420ae39442990805ce4b0",
    "981c32c3d8d6a5f4d651926e2578c5ff",
    "f14421babc90115da21c660140f1a580",
    "7b4a9569db3035dcb6f31ccb08a615b3",
    "e0f0f75697e22b9b10ff68c7c39f4477",
    "c00832bd2dbf3dd3622d87253756eb61"
};

#define TEST_NAME "test md2"

int test_md2()
{
    int failed = 0;
    size_t i = 0;
    unsigned char hash[16];
    char hashStr[33] = { 0 };

    char string[150];
    memset(string, 'a', 150);

    for (; i <= 150; i++) {
        CHashLib_MD2_hash((const unsigned char*) string, i, hash);
        BufferToHex(hash, 16, hashStr, 33);
        if (strcmp(hashStr, expectedHash[i]) != 0) {
            failed++;
        }
    }

    if (failed == 0) {
        printf("%-40s " COLOR_TEXT("OK", COLOR_GREEN) "\n", TEST_NAME);
        return 0;
    }

    printf("%-36s " COLOR_TEXT("FAILED", COLOR_RED) "\n", TEST_NAME);
    return 1;
}
