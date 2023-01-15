#pragma once

#include "common/Aliases.hpp"
#include "common/Atomic.hpp"
#include "common/UniqueAccess.hpp"
#include "controllers/accounts/Account.hpp"
#include "messages/Emote.hpp"
#include "util/QStringHash.hpp"

#include <boost/signals2.hpp>
#include <QColor>
#include <QElapsedTimer>
#include <QString>
#include <rapidjson/document.h>

#include <functional>
#include <mutex>
#include <set>

namespace chatterino {

struct TwitchUser;
class Channel;
using ChannelPtr = std::shared_ptr<Channel>;

class TwitchAccount : public Account
{
public:
    TwitchAccount(const QString &username, const QString &oauthToken_,
                  const QString &oauthClient_, const QString &_userID);

    virtual QString toString() const override;

    const QString &getUserName() const;
    const QString &getOAuthToken() const;
    const QString &getOAuthClient() const;
    const QString &getUserId() const;

    QColor color();
    void setColor(QColor color);

    // Attempts to update the users OAuth Client ID
    // Returns true if the value has changed, otherwise false
    bool setOAuthClient(const QString &newClientID);

    // Attempts to update the users OAuth Token
    // Returns true if the value has changed, otherwise false
    bool setOAuthToken(const QString &newOAuthToken);

    bool isAnon() const;

    void loadBlocks();
    void blockUser(QString userId, std::function<void()> onSuccess,
                   std::function<void()> onFailure);
    void unblockUser(QString userId, std::function<void()> onSuccess,
                     std::function<void()> onFailure);

    SharedAccessGuard<const std::set<QString>> accessBlockedUserIds() const;
    SharedAccessGuard<const std::set<TwitchUser>> accessBlocks() const;

    // Automod actions
    void autoModAllow(const QString msgID, ChannelPtr channel);
    void autoModDeny(const QString msgID, ChannelPtr channel);

    void setGlobalUserStateEmoteSetIDs(QStringList emoteSetIDs);
    [[nodiscard]] QStringList globalUserStateEmoteSetIDs() const;
    [[nodiscard]] std::shared_ptr<const EmoteMap>
        globallyAccessibleTwitchEmotes() const;

private:
    QString oauthClient_;
    QString oauthToken_;
    QString userName_;
    QString userId_;
    const bool isAnon_;
    Atomic<QColor> color_;

    mutable std::mutex ignoresMutex_;
    UniqueAccess<std::set<TwitchUser>> ignores_;
    UniqueAccess<std::set<QString>> ignoresUserIds_;

    QStringList globallyAccessibleEmoteSetIDs_;

    Atomic<std::shared_ptr<const EmoteMap>> globallyAccessibleTwitchEmotes_;

    std::vector<boost::signals2::scoped_connection> bSignals_;
};

}  // namespace chatterino
