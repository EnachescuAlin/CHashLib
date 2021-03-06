#include "md4.h"
#include <stdio.h>
#include <string.h>

#include "linux_color.h"
#include "util.h"

#define TEST_NAME "test md4"

static const char* expectedHash[] = {
    "31d6cfe0d16ae931b73c59d7e0c089c0",
    "bde52cb31de33e46245e05fbdbd6fb24",
    "0de97e6bacb92b24d7578ffb8d58f51e",
    "918d7099b77c7a06634c62ccaf5ebac7",
    "30fdb877509c742c0ef3d63ddbec5146",
    "54485d61c2bf8519c3997d2c17d41b43",
    "9135d5535d445a5adc299d227d3bdbfb",
    "eb393983d7223a7271398da9cd13f13c",
    "23008f046fc579f2d373339ec07f1ef1",
    "a38217d543726545e70685379586f249",
    "55aee4317cf6626378bdd590e1a10009",
    "528bca944a4fc5f156765b0c415a0aea",
    "8f919c346c23b06b46c872be5f80d919",
    "eb50153829a34a8de50ecceec7d44bae",
    "0af8eb203f383dcf6a9d888de443572f",
    "c531cb0a83667b164886e6c1538ad95e",
    "877a3d1769c7fa80a74e7bd9d7602ef3",
    "df84f880a964489d9832af34fa58e591",
    "80e3d8a01982aa1e14994e453d33dd26",
    "f2f147fb12388bece57eca1dcc5ed53f",
    "1d9db7a8b873e64a5c62727edf6d4bbd",
    "cbbe5c1d394bb0b081e960fef4e7ca15",
    "0641e7cd13c7fa26f6da39e83cd31252",
    "76d25193130828accf4d771acb1e51e3",
    "ab434803006332ab606b8c9d284579c9",
    "ea31d4cd2d48469501e09c62da35fdbd",
    "9a374b8b9dd4d3d02ac55036236e7a4d",
    "cc678cd190cbd158e2a111a6a8e6eb4b",
    "dd3d0c638699b8db7d4776a7bf415394",
    "ad4914d6703ec452117852fe99d45e83",
    "d4450595903614027ba328eefa0ea601",
    "b439b841fd3becff4e2dac49d19ed7cf",
    "7dfef9b2eb78b2367246c381c8856478",
    "b3f634cc931234dedf1e51b0015914f9",
    "c9ee7f5964094201ee080b572ef135e0",
    "e02f85b1a7838b905e90e279f27febc8",
    "1254586bfd14e030ce4086fa961ce782",
    "e93b0ebe0fe3c688419faf37511c8f5b",
    "d6d79128936f4b32d01e395aecf29d82",
    "7a0ac9f4f25a7c47afa9aa7df30d3221",
    "2f195c997aada83926fe22847cd3b37c",
    "09354a0a378cfda1ff95a8885d38c4a8",
    "c2256534bfeae9fa1ee7e86187bb965a",
    "fe8f4ae6501ca2898981f60da8c7f6ae",
    "46140f97efbd88928ff112f5367b526a",
    "9d403d371c315ff969baadd8623bc8b3",
    "068d234494f92f646ba378bf505f8c47",
    "af7c0bbed49c6211f1ff4b1739e7ac27",
    "14d946cc28ac58f8c5f210a06c1c6f25",
    "eb8702358201cdace81aaa2db0c6584e",
    "fb2a7c151e17ec3df8502062d86135e3",
    "2d52d26552cbc27cb68eb829e35dd24d",
    "38ab80b7c2b45b568488244adf334410",
    "bd3ed6f7a3a4dd4705360984a18577e5",
    "10993f670d6d785f3e87bc46e8da89dc",
    "c889c81dd86c4d2e025778944ea02881",
    "d5f9a9e9257077a5f08b0b92f348b0ad",
    "872097e6f78e3b53f890459d03bc6fb7",
    "277f5f559a60c0af69efda466786fb30",
    "a70ae7f83d838cce274d7491aa915028",
    "8c6b85becab240ca5db17955c4d39782",
    "672a99ba40462771641359dcc4cb1ddd",
    "5ae7b0c20144bc35483e8d7c16297658",
    "7ea3da77432d44c323671097d1348fc8",
    "52f5076fabd22680234a3fa9f9dc5732",
    "330e377bf231f3cacfecc2c182fe7e5b",
    "095ba42e17c00f9336f807d8bdae72a5",
    "b714fe2e2d4ebc2d801a481ffae39fa9",
    "769051239bb45773c87c19f35071178a",
    "49311d7bb7cc3c078f932e873d7769d2",
    "df01fc1e5dd0bfc600db67201c977efc",
    "09751a7e990fb1d82c0a1293e5f5b3cc",
    "040e619a227c013b5201a9796246d4ae",
    "3470ce6363ed22e5496f138aa7108416",
    "26a8c2b51dc60d23597cca9025119030",
    "e82acdf62a2512470b9580b53df18a2b",
    "c5b92b27da91d2267c23446ecb6a912c",
    "cde8af463ff6018ae7b99ac9de24ea36",
    "a883a850600df1eef28c573e034e7d18",
    "a7cce750192ac057036f1b4c5a2605c8",
    "721a93b051049c47487b06a59acc7d64",
    "f28aa8607f27e972e483638794c1c5ff",
    "577ab2592e92823d26788493457afb35",
    "157bb5e384bbfd04719cbb1eacbac84b",
    "66385a9301518dd05b0f565f08a600ea",
    "0b87dd13cdf6541f400fabe41fa5ba78",
    "a6446864a8bf8d07d57d96dd908ea956",
    "6979b8ecfe581790ac7cd990e8e0736e",
    "f0e85bd3ba0e224fdc2306c256cd5f3a",
    "60fa15155478d3c8a76e5abbdb77cfbe",
    "fcff0a17bd61381b77355cef66808308",
    "828c52051a9693a1b54be9352268955d",
    "53a6b8d4dd7d0770a5f6dc9874e7b88c",
    "00f8653f803627b70ef2e7e1654576c0",
    "14a4d10648330012fe672b650c196021",
    "a6a0b64c05fcd2e57d8cbbc59a1a00b7",
    "ddc02b8e0a315ba8ee08851668a081a9",
    "4067061356fa1e283ec5f3610e7eacf0",
    "717d2ef3060ca3208decae86f9bdcfd9",
    "7b625df18dc2fff7f5244a4c50915893",
    "a2a3c7c3ee6088bad252bfbbae229bb6",
    "547401415a107a8147d3bab71991be0e",
    "e1c162a95ebe24d4a78da81faa6a451b",
    "2a3d6778231dc7ef4ab0d96db648d128",
    "89e6cf2b88c9328a4c348a731d317d25",
    "cf71fec4631db55308ad80186b8dcf37",
    "343ca55fc783302ef9a0b33757e5ef19",
    "aad33b8ff079a18d6425470d011b4d31",
    "357c138b5498b531cb174127fcf14a0f",
    "73b22be5dbad1d26bd9071afebc35856",
    "74101d5e7a9321dad687b4c2ac7e7551",
    "69daeffb60dd1dcfc8a0ddf5ed4dea4f",
    "ccbf3dfa0fac8c6e5c2504cf15777e71",
    "6ee2ad0a2a06e975c2fa8887333de734",
    "8a7defd65211a52a20cbd989bcb079d7",
    "650a6088c41b5951ef46b09f8a8f7a16",
    "f731acbd40496a63fd33c72bff4adc4c",
    "64279e932b0a6cf7fbebc12969ad85f9",
    "5257d42ae36dcfc8418fa40600696e16",
    "e65dd227ccef97fa1d34d70189120f76",
    "b03ddbd470b47c013e0c7ab2ddd763db",
    "e5601aa6994470f918405d745ede163c",
    "6baf506a6e6a525e9ef9bbf7e6b4f45b",
    "d312f30d9fff78e5404f8eac3f0b665f",
    "a7a1c6286070e9a7afa4831d2bf7bafd",
    "941b80acd86c9d9c3f27380591507ded",
    "85c05a6bb4b2cf906813652c68686361",
    "9733b046ad770b4e093b35de4e09e828",
    "cb4a20a561558e29460190c91dced59f",
    "2adcd303c29f93a3ee33a560ece91cd2",
    "52b8ce960bb64e4ec2b579d4047b175e",
    "6ef49aaa109b8120004ffcc801218caf",
    "370ed97adf490f75693cd5fc73a8e3e0",
    "54de78d79ad53da4ce46f945160b591f",
    "0d9014c7b4a9edb3d594056e78d25b9d",
    "4ae5f06e7a0ab2b7142583873acfccfd",
    "c4ca41e447a27ecee443370b002b6459",
    "9a64358c2602da3f21d2e79b21e94bf1",
    "5761a624a7bdedad64e543bc73213e64",
    "d301a78cb6959f11e81bd7a3c6bf5bb3",
    "5d726c762665398737c34803095e91f3",
    "db62b01151a01d5e4a00d87f2a48b98a",
    "c310b6e1016ecb9f5a5c5a4b89f17a76",
    "33c7d6e29f904b27272e75144be07d18",
    "835048e983d82fb0fa151bb8b6fa636e",
    "b9ff2575260e2ad08557eeba52b27cdd",
    "bcccbcfeab174bddb81cc74dd97984f6",
    "9b98a75eded6b5af8c449b75a74c30b3",
    "5f9f642231152dd8cd5caa9b5fc59b5d",
    "84d82189c5458f8647d338fd62ef1667",
    "e23de568fd6f45821048ce04e6cb9936"
};

int test_md4()
{
    int failed = 0;
    size_t i = 0;
    unsigned char hash[16];
    char hashStr[33] = { 0 };

    char string[150];
    memset(string, 'a', 150);

    for (; i <= 150; i++) {
        CHashLib_MD4_hash((const unsigned char*) string, i, hash);
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
