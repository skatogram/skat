#include "discord_rpc_init.h"
#include <ctime>
#include <core/sdk/utils/xorstr.hpp>

void Discord::Initialize()
{
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Initialize(xorstr_("1113965957967257721"), &Handle, 1, NULL);
}

void Discord::Update(const char* username)
{
    DiscordRichPresence discordPresence;

    memset(&discordPresence, 0, sizeof(discordPresence));
    static auto elapsed = std::time(nullptr);

    discordPresence.largeImageText = xorstr_("invis.project");
    discordPresence.details = username;
    discordPresence.state = xorstr_("playing with the best hack in alkad");
    discordPresence.largeImageKey = xorstr_("-1");
    discordPresence.startTimestamp = elapsed;
    discordPresence.button1_label = xorstr_("buy cheat"); // да да я добавил кнопочки =)
    discordPresence.button1_url = xorstr_("https://discord.gg/hUgxMJCcnW");
    discordPresence.button2_label = xorstr_("youtube channel");
    discordPresence.button2_url = xorstr_("https://youtube.com/@kakrazz");
    Discord_UpdatePresence(&discordPresence);
}

void Discord::Shutdown()
{
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Shutdown();
}