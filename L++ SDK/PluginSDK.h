#ifndef PluginSDK_h__
#define PluginSDK_h__

#include "PluginData.h"

#define PLUGIN_API			extern "C" __declspec(dllexport)
#define PLUGIN_EVENT(T)		static T __cdecl
#define PLUGIN_EVENTD(T)	T __cdecl

#define PluginSetup(x) \
	BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpvReserved) { return TRUE; }

#define PluginSDKSetup(x) \
	GPluginSDK			= x; \
	GOrbwalking			= x->GetOrbwalking(); \
	GEventManager		= x->GetEventManager(); \
	GRender				= x->GetRenderer(); \
	GEntityList			= x->GetEntityList(); \
	GGame				= x->GetGame(); \
	GDamage				= x->GetDamage(); \
	GPrediction			= x->GetPrediction(); \
	GHealthPrediction	= x->GetHealthPrediction(); \
	GTargetSelector		= x->GetTargetSelector(); \
	GSpellData 			= x->GetSpellDataReader(); \
	GBuffData			= x->GetBuffDataReader(); \
	GMissileData		= x->GetMissileDataReader(); \
	GNavMesh			= x->GetNavMesh(); \
	GUtility			= x->GetUtility();

/// <summary>
/// Font interface for customization to be rendered in OnRender or OnRenderBehindHud.
/// </summary>
class IFont
{
public:
	/// <summary>
	/// Sets the font color.
	/// </summary>
	/// <param name="Color">The color (RGBA, 0-255).</param>
	virtual void SetColor(Vec4 const& Color) = 0;

	/// <summary>
	/// Sets the location flags such as centering (see eFontLocation).
	/// </summary>
	/// <param name="Flags">The flags.</param>
	virtual void SetLocationFlags(int Flags) = 0;

	/// <summary>
	/// Renders the font string.
	/// </summary>
	/// <param name="XPosition">The x position.</param>
	/// <param name="YPosition">The y position.</param>
	/// <param name="Fmt">The format string.</param>
	/// <param name="...">Additional arguments depending on format.</param>
	virtual void Render(float XPosition, float YPosition, const char* Fmt, ...) = 0;

	/// <summary>
	/// Toggles font outline.
	/// </summary>
	/// <param name="Enabled">if set to <c>true</c> [enabled].</param>
	virtual void SetOutline(bool Enabled) = 0;
};

/// <summary>
/// Texture interface to be rendered in OnRender or OnRenderBehindHud.
/// </summary>
class ITexture
{
public:
	/// <summary>
	/// Scales the texture in both width and height.
	/// </summary>
	/// <param name="ScaledPercent">The scaled percent of original dimensions (0-1).</param>
	virtual void Scale(float ScaledPercent) = 0;

	/// <summary>
	/// Scales the texture in both width and height
	/// </summary>
	/// <param name="WidthPercent">The scaled width percent (0-1).</param>
	/// <param name="HeightPercent">The scaled height percent (0-1).</param>
	virtual void Scale(float WidthPercent, float HeightPercent) = 0;

	/// <summary>
	/// Resizes the texture in both width and height.
	/// </summary>
	/// <param name="Size">Dimension size.</param>
	virtual void Resize(float Size) = 0;

	/// <summary>
	/// Resizes the texture in both width and height.
	/// </summary>
	/// <param name="WidthSize">Width size.</param>
	/// <param name="HeightSize">Height size.</param>
	virtual void Resize(float WidthSize, float HeightSize) = 0;

	/// <summary>
	/// Draws the texture.
	/// </summary>
	/// <param name="XPosition">The x position.</param>
	/// <param name="YPosition">The y position.</param>
	virtual void Draw(float XPosition, float YPosition) = 0;

	/// <summary>
	/// Gets the size.
	/// </summary>
	/// <returns>Size of the texture.</returns>
	virtual Vec2 const& GetSize() = 0;

	/// <summary>
	/// Sets the color.
	/// </summary>
	/// <param name="Color">The color (RGBA, 0-255).</param>
	virtual void SetColor(Vec4 const& Color) = 0;

	/// <summary>
	/// Draws the texture as a circle.
	/// </summary>
	/// <param name="XPosition">The x position.</param>
	/// <param name="YPosition">The y position.</param>
	/// <param name="Radius">The radius.</param>
	virtual void DrawCircle(float XPosition, float YPosition, float Radius) = 0;

	/// <summary>
	/// Sets the scale of the texture so it matches a specific size.
	/// </summary>
	/// <param name="WantedSize">Size of the rescaled texture.</param>
	virtual void SetScaleBySize(Vec2 const& WantedSize) = 0;

	/// <summary>
	/// Gets the scaled size percent relative to the original size.
	/// </summary>
	/// <param name="NewSize">The size to compare for scaled offset.</param>
	/// <returns>Scaled offset.</returns>
	virtual Vec2 const& GetScaledOffset(Vec2 const& NewSize) = 0;

	/// <summary>
	/// Gets the scaled size of the texture.
	/// </summary>
	/// <param name="OriginalSize">Original texture size.</param>
	/// <returns>Scaled size.</returns>
	virtual Vec2 const& GetScaledSize(Vec2 const& OriginalSize) = 0;
};

/// <summary>
/// Interface to be used for rendering shapes and text via render events (OnRender, OnRenderBehindHud, etc.)
/// </summary>
class IRender
{
public:
	/// <summary>
	/// Draws simple text without the use of IFont.
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <param name="Color">The color (RGBA, 0-255).</param>
	/// <param name="Text">The formatted text.</param>
	/// <param name="...">Additional arguments.</param>
	virtual void DrawText(Vec2 const& Position, Vec4 const& Color, const char* Text, ...) = 0;

	/// <summary>
	/// Draws line.
	/// </summary>
	/// <param name="Position1">The start position.</param>
	/// <param name="Position2">The end position.</param>
	/// <param name="Color">The color (RGBA, 0-255).</param>
	virtual void DrawLine(Vec2 const& Position1, Vec2 const& Position2, Vec4 const& Color) = 0;

	/// <summary>
	/// Draws filled box.
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <param name="Size">The size.</param>
	/// <param name="Color">The color (RGBA, 0-255).</param>
	virtual void DrawFilledBox(Vec2 const& Position, Vec2 const& Size, Vec4 const& Color) = 0;

	/// <summary>
	/// Draws outined box.
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <param name="Size">The size.</param>
	/// <param name="Width">The width.</param>
	/// <param name="Color">The color (RGBA, 0-255).</param>
	virtual void DrawOutinedBox(Vec2 const& Position, Vec2 const& Size, float Width, Vec4 const& Color) = 0;

	/// <summary>
	/// Draws outlined circle.
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <param name="Color">The color (RGBA, 0-255).</param>
	/// <param name="Radius">The radius.</param>
	virtual void DrawOutlinedCircle(Vec3 const& Position, Vec4 const& Color, float Radius) = 0;

	/// <summary>
	/// Draws filled circle.
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <param name="Color">The color (RGBA, 0-255).</param>
	/// <param name="Radius">The radius.</param>
	virtual void DrawFilledCircle(Vec3 const& Position, Vec4 const& Color, float Radius) = 0;

	/// <summary>
	/// Creates texture from file.
	/// </summary>
	/// <param name="TextureName">The name of the texture as it appears in the "Textures" directory.</param>
	/// <returns>ITexture or nullptr if failed.</returns>
	virtual ITexture* CreateTextureFromFile(const char* TextureName) = 0;

	/// <summary>
	/// Creates texture from memory.
	/// </summary>
	/// <param name="Data">The texture data.</param>
	/// <param name="DataLength">Length of the data.</param>
	/// <param name="TextureName">Name of the texture.</param>
	/// <returns>ITexture or nullptr if failed.</returns>
	virtual ITexture* CreateTextureFromMemory(uint8_t* Data, uint32_t DataLength, const char* TextureName) = 0;

	/// <summary>
	/// Gets the screen size.
	/// </summary>
	/// <returns>Resolution.</returns>
	virtual Vec2 const& ScreenSize() = 0;

	/// <summary>
	/// Creates a font.
	/// </summary>
	/// <param name="Typeface">The typeface.</param>
	/// <param name="Size">The size.</param>
	/// <param name="Weight">The weight.</param>
	/// <returns>IFont or nullptr if failed.</returns>
	virtual IFont* CreateFont(const char* Typeface, float Size, int Weight = kFontWeightNormal) = 0;

	/// <summary>
	/// Sends a notification to chat and screen corner.
	/// </summary>
	/// <param name="Color">The color (RGBA, 0-255).</param>
	/// <param name="SecondsToShow">The seconds to show.</param>
	/// <param name="Message">The formatted text.</param>
	/// <param name="">Additional arguments.</param>
	virtual void Notification(Vec4 const& Color, DWORD SecondsToShow, const char* Message, ...) = 0;

	/// <summary>
	/// Draws outlined circle.
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <param name="Color">The color (RGBA, 0-255).</param>
	/// <param name="Radius">The radius.</param>
	virtual void DrawOutlinedCircle(Vec2 const& Position, Vec4 const& Color, float Radius) = 0;

	/// <summary>
	/// Extended notification.
	/// </summary>
	/// <param name="Color">The color (RGBA, 0-255).</param>
	/// <param name="SecondsToShow">The seconds to show.</param>
	/// <param name="PrintInChat">if set to <c>true</c> [print in chat].</param>
	/// <param name="ShowInCorner">if set to <c>true</c> [show in corner].</param>
	/// <param name="Fmt">The formatted text.</param>
	/// <param name="...">Additional arguments.</param>
	virtual void NotificationEx(Vec4 const& Color, DWORD SecondsToShow, bool PrintInChat, bool ShowInCorner, const char* Fmt, ...) = 0;

	/// <summary>
	/// Draws a circle.
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <param name="Radius">The radius.</param>
	/// <param name="Color">The color (RGBA, 0-255).</param>
	/// <param name="Width">The width.</param>
	/// <param name="FillCircle">if set to <c>true</c> [fill circle].</param>
	/// <param name="ZEnable">if set to <c>true</c> [zenable].</param>
	virtual void DrawCircle(Vec3 const& Position, float Radius, Vec4 const& Color, float Width = 5.f, bool FillCircle = false, bool ZEnable = false) = 0;
};

/// <summary>
/// Interface for iterating and finding various units in the object list.
/// </summary>
class IEntityList
{
public:
	/// <summary>
	/// Gets the total number of entities.
	/// </summary>
	/// <returns>Total entities in list.</returns>
	virtual int NumberOfEntities() = 0;

	/// <summary>
	/// Gets the entity at specified index.
	/// </summary>
	/// <param name="Idx">The index.</param>
	/// <returns>IUnit or nullptr if failed.</returns>
	virtual IUnit* GetEntityAt(int Idx) = 0;

	/// <summary>
	/// Gets the local player unit.
	/// </summary>
	/// <returns>Local player.</returns>
	virtual IUnit* Player() = 0;

	/// <summary>
	/// Gets all hero units.
	/// </summary>
	/// <param name="Friendly">if set to <c>true</c> [search friendly].</param>
	/// <param name="Enemy">if set to <c>true</c> [search enemy].</param>
	/// <returns>Vector of all units found.</returns>
	virtual std::vector<IUnit*> GetAllHeros(bool Friendly, bool Enemy) = 0;

	/// <summary>
	/// Gets all minions (normal, super, jungle, etc.).
	/// </summary>
	/// <param name="Friendly">if set to <c>true</c> [search friendly].</param>
	/// <param name="Enemy">if set to <c>true</c> [search enemy].</param>
	/// <param name="Neutral">if set to <c>true</c> [search neutral].</param>
	/// <returns>Vector of all units found.</returns>
	virtual std::vector<IUnit*> GetAllMinions(bool Friendly, bool Enemy, bool Neutral) = 0;

	/// <summary>
	/// Gets all turrets.
	/// </summary>
	/// <param name="Friendly">if set to <c>true</c> [search friendly].</param>
	/// <param name="Enemy">if set to <c>true</c> [search enemy].</param>
	/// <returns>Vector of all units found.</returns>
	virtual std::vector<IUnit*> GetAllTurrets(bool Friendly, bool Enemy) = 0;

	/// <summary>
	/// Gets all units.
	/// </summary>
	/// <returns>Vector of all units found.</returns>
	virtual std::vector<IUnit*> GetAllUnits() = 0;

	/// <summary>
	/// Gets all missiles (IUnit.IsMissile == true).
	/// </summary>
	/// <param name="Friendly">if set to <c>true</c> [search friendly].</param>
	/// <param name="Enemy">if set to <c>true</c> [search enemy].</param>
	/// <returns>Vector of all units found.</returns>
	virtual std::vector<IUnit*> GetAllMissiles(bool Friendly, bool Enemy) = 0;

	/// <summary>
	/// Gets all inhibitors.
	/// </summary>
	/// <param name="Friendly">if set to <c>true</c> [search friendly].</param>
	/// <param name="Enemy">if set to <c>true</c> [search enemy].</param>
	/// <returns>Vector of all units found.</returns>
	virtual std::vector<IUnit*> GetAllInhibitors(bool Friendly, bool Enemy) = 0;

	/// <summary>
	/// Gets the enemy nexus.
	/// </summary>
	/// <returns>Enemy nexus unit.</returns>
	virtual IUnit* GetEnemyNexus() = 0;

	/// <summary>
	/// Gets the team nexus.
	/// </summary>
	/// <returns>Team nexus unit.</returns>
	virtual IUnit* GetTeamNexus() = 0;

	/// <summary>
	/// Checks if this object currently exists (can also use IUnit::IsValidObject).
	/// </summary>
	/// <param name="Source">The source.</param>
	/// <returns>
	///   <c>true</c> if this unit exists; otherwise, <c>false</c>.
	/// </returns>
	virtual bool DoesObjectExist(IUnit* Source) = 0;

	/// <summary>
	/// Gets the entity by unique network identifier (IUnit::GetNetworkId).
	/// </summary>
	/// <param name="NetworkId">The network identifier.</param>
	/// <returns>IUnit.</returns>
	virtual IUnit* GetEntityByNetworkId(int NetworkId) = 0;

	/// <summary>
	/// Gets the entity by unique target identifier (IUnit::GetTargetId).
	/// </summary>
	/// <param name="TargetId">The target identifier.</param>
	/// <returns>IUnit.</returns>
	virtual IUnit* GetEntityByTargetId(int TargetId) = 0;

	/// <summary>
	/// Gets all minions (normal, super, jungle, etc.) and wards.
	/// </summary>
	/// <param name="Friendly">if set to <c>true</c> [search friendly].</param>
	/// <param name="Enemy">if set to <c>true</c> [search enemy].</param>
	/// <param name="Neutral">if set to <c>true</c> [search neutral].</param>
	/// <returns>Vector of all units found.</returns>
	virtual std::vector<IUnit*> GetAllMinionsAndWards(bool Friendly, bool Enemy, bool Neutral) = 0;

	/// <summary>
	/// Gets all units of a particular type.
	/// </summary>
	/// <param name="ClassId">The class identifier.</param>
	/// <returns>Vector of all units found.</returns>
	virtual std::vector<IUnit*> GetAllUnitsOfType(eGameObjectClassId ClassId) = 0;

	/// <summary>
	/// Gets all units of multiple specific types.
	/// </summary>
	/// <param name="ClassId">The class identifier.</param>
	/// <returns>Vector of all units found.</returns>
	virtual std::vector<IUnit*> GetAllUnitsOfTypes(std::vector<eGameObjectClassId> ClassIdList) = 0;

	/// <summary>
	/// Gets all units of multiple specific types that match the IsValid callback.
	/// </summary>
	/// <param name="ClassIdList">The class identifier list.</param>
	/// <param name="IsValidCallback">The function callback to check for validity.</param>
	/// <returns>Vector of all units found.</returns>
	virtual std::vector<IUnit*> GetAllUnitsOfTypesEx(std::vector<eGameObjectClassId> ClassIdList, std::function<bool(IUnit*)> IsValidCallback) = 0;
};

/// <summary>
/// Interface for interacting with the game engine.
/// </summary>
class IGame
{
public:
	/// <summary>
	/// Prints input to chat box (not visible to other players).
	/// </summary>
	/// <param name="Input">The HTML formatted input.</param>
	virtual void PrintChat(const char* Input) = 0;

	/// <summary>
	/// Projects a world position to screen coordinates.
	/// </summary>
	/// <param name="WorldPosition">The world position.</param>
	/// <param name="ScreenPositionOut">The output screen position.</param>
	/// <returns>
	///   <c>true</c> if projection was successful; otherwise, <c>false</c>.
	/// </returns>
	virtual bool Projection(Vec3 const& WorldPosition, Vec2* ScreenPositionOut) = 0;

	/// <summary>
	/// Gets networking latency.
	/// </summary>
	/// <returns>Latency.</returns>
	virtual int Latency() = 0;

	/// <summary>
	/// Gets game status code.
	/// </summary>
	/// <returns>Status.</returns>
	virtual int Status() = 0;

	/// <summary>
	/// Gets game time in seconds.
	/// </summary>
	/// <returns>Elapsed seconds.</returns>
	virtual float Time() = 0;

	/// <summary>
	/// Gets world position of cursor (updated properly when cursor is in mini map).
	/// </summary>
	/// <returns>Cursor world position.</returns>
	virtual Vec3 const& CursorPosition() = 0;

	/// <summary>
	/// Issues an order on the source object owned by local player towards the specified position.
	/// </summary>
	/// <param name="Source">The source.</param>
	/// <param name="Order">The order.</param>
	/// <param name="Position">The position.</param>
	/// <returns>
	///   <c>true</c> if order was issued succesfully; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IssueOrder(IUnit* Source, eGameObjectOrder Order, Vec3 const& Position) = 0;

	/// <summary>
	/// Issues an order on the source object owned by local player towards the specified target.
	/// </summary>
	/// <param name="Source">The source.</param>
	/// <param name="Order">The order.</param>
	/// <param name="Target">The target.</param>
	/// <returns>
	///   <c>true</c> if order was issued succesfully; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IssueOrder(IUnit* Source, eGameObjectOrder Order, IUnit* Target) = 0;

	/// <summary>
	/// Gets time interval between each game tick in seconds.
	/// </summary>
	/// <returns>Interval per tick</returns>
	virtual float IntervalPerTick() = 0;

	/// <summary>
	/// Extended PrintChat allowing for optional color if you don't want to specify it in HTML tags.
	/// </summary>
	/// <param name="Message">The input.</param>
	/// <param name="Color">The color (RGBA, 0-255).</param>
	virtual void PrintChatEx(const char* Message, Vec3 const& Color) = 0;

	/// <summary>
	/// Projects a world position to mini map screen coordinates.
	/// </summary>
	/// <param name="World">The world position.</param>
	/// <param name="Minimap">The output screen position.</param>
	/// <returns>
	///   <c>true</c> if projection was successful; otherwise, <c>false</c>.
	/// </returns>
	virtual bool WorldToMinimap(Vec3 const& World, Vec2& Minimap) = 0;

	/// <summary>
	/// Gets the target currently selected by your local player in game.
	/// </summary>
	/// <returns>Selected target.</returns>
	virtual IUnit* GetSelectedTarget() = 0;

	/// <summary>
	/// Shows a ping on your client, not sent to other players.
	/// </summary>
	/// <param name="PingType">Type of the ping.</param>
	/// <param name="Target">The target.</param>
	/// <param name="PlaySound">if set to <c>true</c> [play sound].</param>
	virtual void ShowPing(int PingType, IUnit* Target, bool PlaySound) = 0;

	/// <summary>
	/// Shows a ping on your client, not sent to other players.
	/// </summary>
	/// <param name="PingType">Type of the ping.</param>
	/// <param name="Position">The position.</param>
	/// <param name="PlaySound">if set to <c>true</c> [play sound].</param>
	virtual void ShowPing(int PingType, Vec3 const& Position, bool PlaySound) = 0;

	/// <summary>
	/// Sends a ping, shown to other players.
	/// </summary>
	/// <param name="PingType">Type of the ping.</param>
	/// <param name="Target">The target.</param>
	virtual void SendPing(int PingType, IUnit* Target) = 0;

	/// <summary>
	/// Sends a ping, shown to other players.
	/// </summary>
	/// <param name="PingType">Type of the ping.</param>
	/// <param name="Position">The position.</param>
	virtual void SendPing(int PingType, Vec3 const& Position) = 0;

	/// <summary>
	/// Gets the type of the game.
	/// </summary>
	/// <returns>Game type (eGameType).</returns>
	virtual int GetGameType() = 0;

	/// <summary>
	/// Gets the map identifier.
	/// </summary>
	/// <returns>Map id (eMapType).</returns>
	virtual int GetMapId() = 0;

	/// <summary>
	/// Sends out a typed message to other players in the chatbox.
	/// </summary>
	/// <param name="Fmt">The formatted text.</param>
	/// <param name="...">Additional arguments.</param>
	virtual void Say(const char* Fmt, ...) = 0;

	/// <summary>
	/// Sends a taunt.
	/// </summary>
	/// <param name="TauntId">The taunt identifier.</param>
	virtual void Taunt(int TauntId) = 0;

	/// <summary>
	/// Buys the item.
	/// </summary>
	/// <param name="ItemId">The item identifier.</param>
	/// <returns>
	///   <c>true</c> if buy was successful; otherwise, <c>false</c>.
	/// </returns>
	virtual bool BuyItem(int ItemId) = 0;

	/// <summary>
	/// Sells the item.
	/// </summary>
	/// <param name="Slot">The slot (eSpellSlot).</param>
	/// <returns>
	///   <c>true</c> if sell was successful; otherwise, <c>false</c>.
	/// </returns>
	virtual bool SellItem(int Slot) = 0;

	/// <summary>
	/// Undo the previous buy.
	/// </summary>
	virtual void UndoBuy() = 0;

	/// <summary>
	/// Swaps two item slots.
	/// </summary>
	/// <param name="Slot1">The first slot (eSpellSlot).</param>
	/// <param name="Slot2">The second slot (eSpellSlot).</param>
	virtual void SwapItems(int Slot1, int Slot2) = 0;

	/// <summary>
	/// Quits the game.
	/// </summary>
	virtual void Quit() = 0;

	/// <summary>
	/// Determines whether local player [can level up spell] at the specified slot.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>
	///   <c>true</c> if local player [can level up spell] at the specified slot; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CanLevelUpSpell(int Slot) = 0;

	/// <summary>
	/// Extended projection for points that lie outside of screen space but can still be shown (useful for DrawLine).
	/// Instead of checking if it returns true as you would would the previous projection, you should check z.
	/// If the z value is less than 1.0 then it is safe to render the point, otherwise don't.
	/// </summary>
	/// <param name="WorldPosition">The world position.</param>
	/// <param name="ScreenPositionOut">The screen position out.</param>
	/// <returns>
	///   <c>true</c> if world position is inside screen coordinates; otherwise, <c>false</c>.
	/// </returns>
	virtual bool Projection(Vec3 const& WorldPosition, Vec3* ScreenPositionOut) = 0;

	/// <summary>
	/// Gets the current game time in milliseconds.
	/// </summary>
	/// <returns>Elapsed time.</returns>
	virtual int TickCount() = 0;

	/// <summary>
	/// Gets the current tick, incremented each time a game tick has been executed.
	/// </summary>
	/// <returns>Game tick.</returns>
	virtual int CurrentTick() = 0;

	/// <summary>
	/// Determines whether [is chat open].
	/// </summary>
	/// <returns>
	///   <c>true</c> if [is chat open]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsChatOpen() = 0;

	/// <summary>
	/// Projects screen coordinates to world position.
	/// </summary>
	/// <param name="ScreenPosition">The screen position.</param>
	/// <param name="WorldPosition">The output world position.</param>
	virtual void ScreenToWorld(Vec2 const& ScreenPosition, Vec3* WorldPosition) = 0;

	/// <summary>
	/// Determines whether [is within fog of war] [the specified position].
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <returns>
	///   <c>true</c> if [is within fog of war] [the specified position]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool WithinFogOfWar(Vec3 const& Position) = 0;

	/// <summary>
	/// Determines whether [is shop open].
	/// </summary>
	/// <returns>
	///   <c>true</c> if [is shop open]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsShopOpen() = 0;

	/// <summary>
	/// Determines whether [is scoreboard open].
	/// </summary>
	/// <returns>
	///   <c>true</c> if [is scoreboard open]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsScoreboardOpen() = 0;

	/// <summary>
	/// Extended IssueOrder to toggle whether plugin events get triggered.
	/// </summary>
	/// <param name="Source">The source.</param>
	/// <param name="Order">The order.</param>
	/// <param name="Position">The position.</param>
	/// <param name="TriggerEvents">if set to <c>true</c> [trigger events].</param>
	/// <returns>
	///   <c>true</c> if order was issued succesfully; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IssueOrderEx(IUnit* Source, eGameObjectOrder Order, Vec3 const& Position, bool TriggerEvents) = 0;

	/// <summary>
	/// Extended IssueOrder to toggle whether plugin events get triggered
	/// </summary>
	/// <param name="Source">The source.</param>
	/// <param name="Order">The order.</param>
	/// <param name="Target">The target.</param>
	/// <param name="TriggerEvents">if set to <c>true</c> [trigger events].</param>
	/// <returns>
	///   <c>true</c> if order was issued succesfully; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IssueOrderEx(IUnit* Source, eGameObjectOrder Order, IUnit* Target, bool TriggerEvents) = 0;
};

/// <summary>
/// Interface for determining damage values.
/// </summary>
class IDamage
{
public:
	/// <summary>
	/// Gets the auto attack damage.
	/// </summary>
	/// <param name="Source">The source.</param>
	/// <param name="Target">The target.</param>
	/// <param name="Use_Passives">if set to <c>true</c> [use passives] in calculations.</param>
	/// <returns>Final calculated damage.</returns>
	virtual double GetAutoAttackDamage(IUnit* Source, IUnit* Target, bool Use_Passives) = 0;

	/// <summary>
	/// Calculates the physical damage.
	/// </summary>
	/// <param name="Source">The source.</param>
	/// <param name="Target">The target.</param>
	/// <param name="Damage">The initial damage.</param>
	/// <returns>Final calculated damage.</returns>
	virtual double CalcPhysicalDamage(IUnit* Source, IUnit* Target, double Damage) = 0;

	/// <summary>
	/// Gets the summoner spell damage.
	/// </summary>
	/// <param name="Source">The source.</param>
	/// <param name="Target">The target.</param>
	/// <param name="SummonerSpell">The summoner spell.</param>
	/// <returns>Final calculated damage.</returns>
	virtual double GetSummonerSpellDamage(IUnit* Source, IUnit* Target, eSummonerSpell SummonerSpell) = 0;

	/// <summary>
	/// Gets the spell damage by slot.
	/// </summary>
	/// <param name="Source">The source.</param>
	/// <param name="Target">The target.</param>
	/// <param name="Slot">The slot.</param>
	/// <returns>Final calculated damage.</returns>
	virtual double GetSpellDamage(IUnit* Source, IUnit* Target, int Slot) = 0;

	/// <summary>
	/// Calculates mixed damage using multiple damage types.
	/// </summary>
	/// <param name="Source">The source.</param>
	/// <param name="Target">The target.</param>
	/// <param name="PhysicalDamage">The initial physical damage.</param>
	/// <param name="MagicDamage">The initial magic damage.</param>
	/// <param name="MagicPct">The percent of damage that's magical (0-100).</param>
	/// <param name="PhysicalPct">The percent of damage that's physical (0-100).</param>
	/// <param name="TruePct">The percent of damage that's true (0-100).</param>
	/// <returns>Final calculated damage.</returns>
	virtual double CalcMixedDamage(IUnit* Source, IUnit* Target, double PhysicalDamage, double MagicDamage, int MagicPct, int PhysicalPct, int TruePct) = 0;

	/// <summary>
	/// Calculates the magic damage.
	/// </summary>
	/// <param name="Source">The source.</param>
	/// <param name="Target">The target.</param>
	/// <param name="Damage">The initial damage.</param>
	/// <returns>Final calculated damage.</returns>
	virtual double CalcMagicDamage(IUnit* Source, IUnit* Target, double Damage) = 0;

	/// <summary>
	/// Gets the spell damage by slot and stage.
	/// </summary>
	/// <param name="Source">The source.</param>
	/// <param name="Target">The target.</param>
	/// <param name="Slot">The slot.</param>
	/// <param name="Stage">The stage.</param>
	/// <returns>Final calculated damage.</returns>
	virtual double GetSpellDamage(IUnit* Source, IUnit* Target, int Slot, int Stage) = 0;
};

/// <summary>
/// Interface for finding the best target to attack.
/// </summary>
class ITargetSelector
{
public:
	/// <summary>
	/// Finds the best target.
	/// </summary>
	/// <param name="Priority">The priority to use when searching.</param>
	/// <param name="Type">The damage type to use when searching.</param>
	/// <param name="Range">The max range.</param>
	/// <returns>Target found.</returns>
	virtual IUnit* FindTarget(eTargetPriority Priority, eDamageType Type, float Range) = 0;

	/// <summary>
	/// Gets the target currently focused by the target selector, if any.
	/// </summary>
	/// <returns>Focused target.</returns>
	virtual IUnit* GetFocusedTarget() = 0;

	/// <summary>
	/// Sets the focused target, nullptr to remove.
	/// </summary>
	/// <param name="Focused">The focused.</param>
	virtual void SetOverrideFocusedTarget(IUnit* Focused) = 0;

	/// <summary>
	/// Finds the best target
	/// </summary>
	/// <param name="Priority">How to prioritize the best target</param>
	/// <param name="Type">Damage type for calculations</param>
	/// <param name="Range">Max range</param>
	/// <param name="RangeCheckFrom">Optional start position for range checks</param>
	/// <param name="IgnoreSpellShields">If set to <c>true</c> [ignore shields].</param>
	/// <param name="IgnoredChamps">Champions to ignore</param>
	/// <param name="Conditions">Currently unused</param>
	/// <returns>Best target found or nullptr</returns>
	virtual IUnit* FindTargetEx(eTargetPriority Priority, eDamageType Type, float Range, Vec3* RangeCheckFrom = nullptr, bool IgnoreSpellShields = true, std::vector<IUnit*>* IgnoredChamps = nullptr, void* Conditions = nullptr) = 0;
};

/// <summary>
/// Interface for running prediction.
/// </summary>
class IPrediction
{
public:
	/// <summary>
	/// Gets the future unit position given his current path and speed.
	/// </summary>
	/// <param name="Player">The player.</param>
	/// <param name="FutureSeconds">The future seconds.</param>
	/// <param name="IncludeLatency">if set to <c>true</c> [include latency].</param>
	/// <param name="Out">The output position.</param>
	virtual void GetFutureUnitPosition(IUnit* Player, float FutureSeconds, bool IncludeLatency, Vec3& Out) = 0;

	/// <summary>
	/// Creates a physics simulation to find the best hit position for a given target.
	/// Missile and target are both moved forward in time, with trajectory being recalculated each
	/// delta, until a collision is found or the missile goes out of range. Returns the entity
	/// hit and is not guaranteed to be your target so the return should always be checked.
	/// </summary>
	/// <param name="StartPosition">The start position.</param>
	/// <param name="Target">The target.</param>
	/// <param name="Speed">The speed.</param>
	/// <param name="Radius">The radius.</param>
	/// <param name="Range">The range.</param>
	/// <param name="Delay">The delay.</param>
	/// <param name="CollisionFlags">The collision flags (eCollisionFlags).</param>
	/// <param name="CastPosition">The output cast position.</param>
	/// <returns></returns>
	virtual IUnit* SimulateMissile(Vec3 const& StartPosition, IUnit* Target, float Speed, float Radius, float Range, float Delay, int CollisionFlags, Vec3& CastPosition) = 0;

	/// <summary>
	/// Finds best AoE cast position that will hit the most targets (line AoE if IsMissile is true, circle AoE otherwise).
	/// </summary>
	/// <param name="Range">The range.</param>
	/// <param name="Radius">The radius.</param>
	/// <param name="IsMissile">if set to <c>true</c> [is missile].</param>
	/// <param name="CheckMinions">if set to <c>true</c> [check minions].</param>
	/// <param name="CheckHeroes">if set to <c>true</c> [check heroes].</param>
	/// <param name="CastPosition">The output cast position.</param>
	/// <param name="EnemiesHit">The output enemies hit.</param>
	virtual void FindBestCastPosition(float Range, float Radius, bool IsMissile, bool CheckMinions, bool CheckHeroes, Vec3& CastPosition, int& EnemiesHit) = 0;

	/// <summary>
	/// Visibility check across a ray.
	/// </summary>
	/// <param name="StartPosition">The start position.</param>
	/// <param name="EndPosition">The end position.</param>
	/// <param name="CollisionPositionOut">The collision position out.</param>
	/// <param name="CollisionFlagsOut">The collision flags out (eMeshType).</param>
	/// <returns></returns>
	virtual bool TestLineOfSight(Vec3 const& StartPosition, Vec3 const& EndPosition, Vec3& CollisionPositionOut, int& CollisionFlagsOut) = 0;

	/// <summary>
	/// Finds best AoE cast position that will hit the most targets (line AoE if IsMissile is true, circle AoE otherwise).
	/// </summary>
	/// <param name="Range">The range.</param>
	/// <param name="Radius">The radius.</param>
	/// <param name="IsMissile">if set to <c>true</c> [is missile].</param>
	/// <param name="CheckMinions">if set to <c>true</c> [check minions].</param>
	/// <param name="CheckHeroes">if set to <c>true</c> [check heroes].</param>
	/// <param name="CastPosition">The output cast position.</param>
	/// <param name="EnemiesHit">The output enemies hit.</param>
	/// <param name="Delay">The delay.</param>
	virtual void FindBestCastPosition(float Range, float Radius, bool IsMissile, bool CheckMinions, bool CheckHeroes, Vec3& CastPosition, int& EnemiesHit, float Delay) = 0;

	/// <summary>
	/// Gets the collision flags for point.
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <returns>Collision flags (eMeshType).</returns>
	virtual int GetCollisionFlagsForPoint(Vec3 const& Position) = 0;

	/// <summary>
	/// Determines whether [is point wall] [the specified position].
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <returns>
	///   <c>true</c> if [is point wall] [the specified position]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsPointWall(Vec3 const& Position) = 0;

	/// <summary>
	/// Determines whether [is point grass] [the specified position].
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <returns>
	///   <c>true</c> if [is point grass] [the specified position]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsPointGrass(Vec3 const& Position) = 0;

	/// <summary>
	/// Runs the prediction.
	/// </summary>
	/// <param name="Input">The input.</param>
	/// <param name="Output">The output.</param>
	/// <param name="PredictionVersion">The prediction version, should remain default unless you know what you're doing.</param>
	virtual void RunPrediction(AdvPredictionInput* Input, AdvPredictionOutput* Output, uint32_t PredictionVersion = 1) = 0;

	/// <summary>
	/// Extended FindBestCastPosition to accept and return more detailed information.
	/// </summary>
	/// <param name="StartPosition">The start position.</param>
	/// <param name="Delay">The delay.</param>
	/// <param name="Range">The range.</param>
	/// <param name="Radius">The radius.</param>
	/// <param name="IsMissile">if set to <c>true</c> [is missile].</param>
	/// <param name="CheckMinions">if set to <c>true</c> [check minions].</param>
	/// <param name="CheckHeroes">if set to <c>true</c> [check heroes].</param>
	/// <param name="CastPosition">The output cast position.</param>
	/// <param name="EnemiesHit">The output enemies hit.</param>
	virtual void FindBestCastPositionEx(Vec3 const& StartPosition, float Delay, float Range, float Radius, bool IsMissile, bool CheckMinions, bool CheckHeroes, Vec3& CastPosition, std::vector<IUnit*>& EnemiesHit) = 0;
};

/// <summary>
/// Interface for plugin menu controls.
/// </summary>
class IMenuOption
{
public:
	/// <summary>
	/// Gets check box status.
	/// </summary>
	/// <returns>Current check box value.</returns>
	virtual bool Enabled() = 0;

	/// <summary>
	/// Gets the integer.
	/// </summary>
	/// <returns>Current whole number value.</returns>
	virtual int GetInteger() = 0;

	/// <summary>
	/// Gets the float.
	/// </summary>
	/// <returns>Current floating point value.</returns>
	virtual float GetFloat() = 0;

	/// <summary>
	/// Gets the color.
	/// </summary>
	/// <returns>Current color value.</returns>
	virtual DWORD GetColor() = 0;

	/// <summary>
	/// Gets the color.
	/// </summary>
	/// <param name="OutColor">Output current color value.</param>
	virtual void GetColor(Vec4* OutColor) = 0;

	/// <summary>
	/// Updates the integer.
	/// </summary>
	/// <param name="NewValue">The new value.</param>
	virtual void UpdateInteger(int NewValue) = 0;

	/// <summary>
	/// Updates the float.
	/// </summary>
	/// <param name="NewValue">The new value.</param>
	virtual void UpdateFloat(float NewValue) = 0;

	/// <summary>
	/// Updates the color.
	/// </summary>
	/// <param name="NewValue">The new value.</param>
	virtual void UpdateColor(DWORD NewValue) = 0;
};

/// <summary>
/// Interface for plugin menu parents.
/// </summary>
class IMenu
{
public:
	/// <summary>
	/// Adds another parent menu to this parent.
	/// </summary>
	/// <param name="Title">The title.</param>
	/// <returns>IMenu.</returns>
	virtual IMenu* AddMenu(const char* Title) = 0;

	/// <summary>
	/// Adds a toggled check box control.
	/// Return->Enabled() to see current toggle value.
	/// </summary>
	/// <param name="Name">The name.</param>
	/// <param name="Value">The value.</param>
	/// <returns>IMenuOption</returns>
	virtual IMenuOption* CheckBox(const char* Name, bool Value) = 0;

	/// <summary>
	/// Adds a whole number slider control.
	/// Return->GetInteger() to see current whole number value.
	/// </summary>
	/// <param name="Name">The name.</param>
	/// <param name="MinValue">The minimum value.</param>
	/// <param name="MaxValue">The maximum value.</param>
	/// <param name="Value">The value.</param>
	/// <returns>IMenuOption.</returns>
	virtual IMenuOption* AddInteger(const char* Name, int MinValue, int MaxValue, int Value) = 0;

	/// <summary>
	/// Adds a floating point slider control.
	/// Current->GetFloat() to see current floating point value.
	/// </summary>
	/// <param name="Name">The name.</param>
	/// <param name="MinValue">The minimum value.</param>
	/// <param name="MaxValue">The maximum value.</param>
	/// <param name="Value">The value.</param>
	/// <returns>IMenuOption.</returns>
	virtual IMenuOption* AddFloat(const char* Name, float MinValue, float MaxValue, float Value) = 0;

	/// <summary>
	/// Adds a color picker control.
	/// Return->GetColor() to see current selected color.
	/// </summary>
	/// <param name="Name">The name.</param>
	/// <param name="Value">The default value.</param>
	/// <returns>IMenuOption.</returns>
	virtual IMenuOption* AddColor(const char* Name, DWORD Value) = 0;

	/// <summary>
	/// Adds a color picker control.
	/// Return->GetColor() to see current selected color.
	/// </summary>
	/// <param name="Name">The name.</param>
	/// <param name="Red">The red.</param>
	/// <param name="Green">The green.</param>
	/// <param name="Blue">The blue.</param>
	/// <param name="Alpha">The alpha.</param>
	/// <returns>IMenuOption.</returns>
	virtual IMenuOption* AddColor(const char* Name, float Red, float Green, float Blue, float Alpha) = 0;

	/// <summary>
	/// Saves all options for this menu.
	/// Not entirely necessary as the core will auto save all plugin settings at the end of each game.
	/// </summary>
	virtual void SaveSettings() = 0;

	/// <summary>
	/// Removes this menu parent from the core.
	/// </summary>
	virtual void Remove() = 0;

	/// <summary>
	/// Gets the IMenuOption control child for this parent given the name.
	/// </summary>
	/// <param name="Name">The name.</param>
	/// <returns>IMenuOption.</returns>
	virtual IMenuOption* GetOption(const char* Name) = 0;

	/// <summary>
	/// Adds a key selection drop down box control.
	/// Return->GetInteger() to see key value as defined by a virtual key code.
	/// List of virtual key codes: http://cherrytree.at/misc/vk.htm
	/// </summary>
	/// <param name="Name">The name.</param>
	/// <param name="DefaultKey">The default key.</param>
	/// <returns>IMenuOption.</returns>
	virtual IMenuOption* AddKey(const char* Name, int DefaultKey) = 0;

	/// <summary>
	/// Adds a drop down box selection control.
	/// Return->GetInteger() to get the current selected index.
	/// </summary>
	/// <param name="Name">The name.</param>
	/// <param name="DefaultIdx">The default index.</param>
	/// <param name="Names">Array of names to be used.</param>
	/// <returns>IMenuOption.</returns>
	virtual IMenuOption* AddSelection(const char* Name, int DefaultIdx, std::vector<std::string> const& Names) = 0;
};

/// <summary>
/// Interface for adding and removing plugin events.
/// </summary>
class IEventManager
{
public:
	/// <summary>
	/// Adds the event handler.
	/// </summary>
	/// <param name="EventId">The event identifier.</param>
	/// <param name="CallbackFn">The callback function.</param>
	virtual void AddEventHandler(eLeagueEvents EventId, LPVOID CallbackFn) = 0;

	/// <summary>
	/// Removes the event handler.
	/// </summary>
	/// <param name="EventId">The event identifier.</param>
	/// <param name="CallbackFn">The callback function.</param>
	virtual void RemoveEventHandler(eLeagueEvents EventId, LPVOID CallbackFn) = 0;
};

/// <summary>
/// Interface for predicting unit health after a specified time.
/// </summary>
class IHealthPrediction
{
public:
	/// <summary>
	/// Gets the predicted health after an elapsed time.
	/// </summary>
	/// <param name="Source">The source.</param>
	/// <param name="Prediction">The prediction.</param>
	/// <param name="TimeMs">The time ms.</param>
	/// <param name="DelayMs">The delay ms.</param>
	/// <returns>Predicted health.</returns>
	virtual float GetPredictedHealth(IUnit* Source, eHealthPredictionType Prediction, int TimeMs, int DelayMs) = 0;

	/// <summary>
	/// Gets the predicted damage for a unit accounting for all incoming spells as well as your own damage from the passed spell slot.
	/// </summary>
	/// <param name="Target">The target.</param>
	/// <param name="SpellSlot">The spell slot.</param>
	/// <param name="Delay">The delay in seconds.</param>
	/// <param name="IncludeSkillshots">if set to <c>true</c> [include skillshots] in calculation.</param>
	/// <returns>Total damage after elapsed time.</returns>
	virtual float GetKSDamage(IUnit* Target, int SpellSlot, float Delay, bool IncludeSkillshots) = 0;
};

/// <summary>
/// Deprecated interface for handling spells (use ISpell2).
/// </summary>
class ISpell
{
public:
	/// <summary>
	/// Initializes the spell values.
	/// </summary>
	/// <param name="Params">The parameters.</param>
	virtual void SetupSpell(SpellParams const& Params) = 0;

	/// <summary>
	/// Casts the on unit.
	/// </summary>
	/// <param name="Target">The target.</param>
	/// <returns>
	///   <c>true</c> if [cast was successful]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CastOnUnit(IUnit* Target) = 0;

	/// <summary>
	/// Casts on specified position.
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <returns>
	///   <c>true</c> if [cast was successful]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CastOnPosition(Vec3 const& Position) = 0;

	/// <summary>
	/// Casts from position.
	/// </summary>
	/// <param name="From">The start position.</param>
	/// <param name="To">The end position.</param>
	/// <returns>
	///   <c>true</c> if [cast was successful]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CastFromPosition(Vec3 const& From, Vec3 const& To) = 0;

	/// <summary>
	/// Casts on local player.
	/// </summary>
	/// <returns></returns>
	virtual bool CastOnPlayer() = 0;

	/// <summary>
	/// Sets the spell slot.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	virtual void SetSpellSlot(eSpellSlot Slot) = 0;

	/// <summary>
	/// Sets the spell range.
	/// </summary>
	/// <param name="Range">The range.</param>
	virtual void SetSpellRange(float Range) = 0;

	/// <summary>
	/// Gets the spell range.
	/// </summary>
	/// <returns>Spell range.</returns>
	virtual float GetSpellRange() = 0;

	/// <summary>
	/// Gets the spell slot.
	/// </summary>
	/// <returns>Spell slot.</returns>
	virtual eSpellSlot GetSpellSlot() = 0;

	/// <summary>
	/// Determines whether this instance is ready.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this spell is ready to cast; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsReady() = 0;

	/// <summary>
	/// Sets the spell as a skill shot.
	/// </summary>
	/// <param name="Delay">The delay.</param>
	/// <param name="Width">The width.</param>
	/// <param name="Speed">The speed.</param>
	/// <param name="Collision">if set to <c>true</c> [check collisions].</param>
	/// <param name="Type">The type.</param>
	virtual void SetSkillshot(float Delay, float Width, float Speed, bool Collision, eSpellType Type) = 0;

	/// <summary>
	/// Sets all skill shot values (except delay) from the engine.
	/// </summary>
	/// <param name="Delay">The delay.</param>
	virtual void SetPhysicsVarsFromSpellbook(float Delay) = 0;

	/// <summary>
	/// Gets the speed.
	/// </summary>
	/// <returns>Speed.</returns>
	virtual float GetSpeed() = 0;

	/// <summary>
	/// Gets the radius.
	/// </summary>
	/// <returns>Radius.</returns>
	virtual float GetRadius() = 0;

	/// <summary>
	/// Gets the delay.
	/// </summary>
	/// <returns>Delay.</returns>
	virtual float GetDelay() = 0;

	/// <summary>
	/// Gets the mana cost.
	/// </summary>
	/// <returns>Mana cost.</returns>
	virtual float GetManaCost() = 0;
};

/// <summary>
/// Interface for handling spells.
/// </summary>
class ISpell2
{
public:
	/// <summary>
	/// Runs prediction and casts on target.
	/// </summary>
	/// <param name="Target">The target.</param>
	/// <param name="MinimumHitChance">The minimum hit chance for casting.</param>
	/// <returns>
	///   <c>true</c> if [cast was successful]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CastOnTarget(IUnit* Target, int MinimumHitChance = kHitChanceHigh) = 0;

	/// <summary>
	/// Runs AoE prediction and casts on target.
	/// </summary>
	/// <param name="Target">The target.</param>
	/// <param name="MinimumChampionsHit">The minimum champions hit for casting.</param>
	/// <param name="MinimumHitChance">The minimum hit chance for casting.</param>
	/// <returns>
	///   <c>true</c> if [cast was successful]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CastOnTargetAoE(IUnit* Target, int MinimumChampionsHit = 2, int MinimumHitChance = kHitChanceHigh) = 0;

	/// <summary>
	/// Runs prediction and attempts to last hit any minions.
	/// </summary>
	/// <returns>
	///   <c>true</c> if [minion was attacked]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool LastHitMinion() = 0;

	/// <summary>
	/// Runs prediction (AoE if MinimumEnemiesHit > 1) and attacks the best position.
	/// If MinimumEnemiesHit is greater than 1 then this must be initialized as an AoE spell.
	/// </summary>
	/// <param name="MinimumEnemiesHit">The minimum enemies hit.</param>
	/// <returns>
	///   <c>true</c> if [minion was attacked]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool AttackMinions(int MinimumEnemiesHit = 3) = 0;

	/// <summary>
	/// Casts on local player.
	/// </summary>
	/// <returns>
	///   <c>true</c> if [cast was successful]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CastOnPlayer() = 0;

	/// <summary>
	/// Casts directly on position, no prediction used.
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <returns>
	///   <c>true</c> if [cast was successful]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CastOnPosition(Vec3 const& Position) = 0;

	/// <summary>
	/// Casts directly on unit, no prediction used.
	/// </summary>
	/// <param name="Target">The target.</param>
	/// <returns>
	///   <c>true</c> if [cast was successful]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CastOnUnit(IUnit* Target) = 0;

	/// <summary>
	/// Finds the best AoE cast position that will hit the most targets.
	/// </summary>
	/// <param name="IncludeMinions">if set to <c>true</c> [include minions in search].</param>
	/// <param name="IncludeHeroes">if set to <c>true</c> [include heroes in search].</param>
	/// <param name="CastPosition">The output cast position.</param>
	/// <param name="EnemiesHit">The output enemies hit.</param>
	virtual void FindBestCastPosition(bool IncludeMinions, bool IncludeHeroes, Vec3& CastPosition, int& EnemiesHit) = 0;

	/// <summary>
	/// Wrapper for ITargetSelector::FindTarget using spell range and eTargetPriority::QuickestKill.
	/// </summary>
	/// <param name="DamageType">Type of the damage.</param>
	/// <returns></returns>
	virtual IUnit* FindTarget(eDamageType DamageType) = 0;

	/// <summary>
	/// Determines whether this instance is ready.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this spell is ready to cast; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsReady() = 0;

	/// <summary>
	/// Gets the mana cost.
	/// </summary>
	/// <returns>Mana cost.</returns>
	virtual float ManaCost() = 0;

	/// <summary>
	/// Gets the range.
	/// For charged spells this will return max charged range while not charging and proper charged range during charge.
	/// </summary>
	/// <returns>Range.</returns>
	virtual float Range() = 0;

	/// <summary>
	/// Gets the radius.
	/// </summary>
	/// <returns>Radius.</returns>
	virtual float Radius() = 0;

	/// <summary>
	/// Gets the speed.
	/// </summary>
	/// <returns>Speed.</returns>
	virtual float Speed() = 0;

	/// <summary>
	/// Gets the delay.
	/// </summary>
	/// <returns>Delay.</returns>
	virtual float GetDelay() = 0;

	/// <summary>
	/// Sets the override speed (0 to revert to engine values).
	/// </summary>
	/// <param name="Value">The speed.</param>
	virtual void SetOverrideSpeed(float Value) = 0;

	/// <summary>
	/// Sets the override delay (0 to revert to engine values).
	/// </summary>
	/// <param name="Value">The delay.</param>
	virtual void SetOverrideDelay(float Value) = 0;

	/// <summary>
	/// Sets the override range (0 to rever to engine values).
	/// </summary>
	/// <param name="Value">The range.</param>
	virtual void SetOverrideRange(float Value) = 0;

	/// <summary>
	/// Sets the override radius (0 to revert to engine values).
	/// </summary>
	/// <param name="Value">The radius.</param>
	virtual void SetOverrideRadius(float Value) = 0;

	/// <summary>
	/// Sets multiple skill shot overrides at once (0 to revert to engine values).
	/// </summary>
	/// <param name="OverrideDelay">The override delay.</param>
	/// <param name="OverrideRadius">The override radius.</param>
	/// <param name="OverrideSpeed">The override speed.</param>
	/// <param name="OverrideRange">The override range.</param>
	virtual void SetSkillshot(float OverrideDelay, float OverrideRadius, float OverrideSpeed, float OverrideRange) = 0;

	/// <summary>
	/// Sets the spell as charged.
	/// </summary>
	/// <param name="RangeMin">The minimum charged range.</param>
	/// <param name="RangeMax">The maximum charged range.</param>
	/// <param name="DeltaTime">The delta time in seconds to reach max charge range.</param>
	virtual void SetCharged(float RangeMin, float RangeMax, float DeltaTime) = 0;

	/// <summary>
	/// Determines whether this spell is charging.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this spell is charging; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsCharging() = 0;

	/// <summary>
	/// Starts charging the spell.
	/// </summary>
	virtual void StartCharging() = 0;

	/// <summary>
	/// Starts charging the spell on a position.
	/// </summary>
	/// <param name="Position">The position.</param>
	virtual void StartCharging(Vec3 const& Position) = 0;

	/// <summary>
	/// Gets the current charge percent (0-100).
	/// </summary>
	/// <returns></returns>
	virtual float GetChargePercent() = 0;

	/// <summary>
	/// Gets the spell slot.
	/// </summary>
	/// <returns>Spell slot (eSpellSlot).</returns>
	virtual int GetSlot() = 0;

	/// <summary>
	/// Sets start position for prediction (Vec3(0, 0, 0) to reset).
	/// </summary>
	/// <param name="Position">The position.</param>
	virtual void SetFrom(Vec3 const& Position) = 0;

	/// <summary>
	/// Sets from position for range checks in prediction (Vec3(0, 0, 0) to reset).
	/// </summary>
	/// <param name="Position">The position.</param>
	virtual void SetRangeCheckFrom(Vec3 const& Position) = 0;

	/// <summary>
	/// Runs spell prediction for more detailed output than CastOnTarget.
	/// </summary>
	/// <param name="Target">The target.</param>
	/// <param name="IsAoE">if set to <c>true</c> [is AoE].</param>
	/// <param name="CollisionFlags">The collision flags.</param>
	/// <param name="Output">The output.</param>
	/// <param name="PredictionVersion">The prediction version (for internal use).</param>
	/// <returns>
	///   <c>true</c> if [prediction was run]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool RunPrediction(IUnit* Target, bool IsAoE, int CollisionFlags, AdvPredictionOutput* Output, uint32_t PredictionVersion = 1) = 0;

	/// <summary>
	/// Casts directly from a start position towards an end position, no prediction used.
	/// </summary>
	/// <param name="StartPosition">The start position.</param>
	/// <param name="EndPosition">The end position.</param>
	/// <returns>
	///   <c>true</c> if [cast was successful]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CastFrom(Vec3 const& StartPosition, Vec3 const& EndPosition) = 0;

	/// <summary>
	/// Gets the spell type.
	/// </summary>
	/// <returns>Type (eSpellType).</returns>
	virtual eSpellType GetType() = 0;

	/// <summary>
	/// Gets the range check position or Vec3(0, 0, 0) if it's not being used.
	/// </summary>
	/// <returns>Range check from position.</returns>
	virtual Vec3 const& GetRangeCheckFrom() = 0;

	/// <summary>
	/// Gets the collision flags used for prediction.
	/// </summary>
	/// <returns>Collision flags (eCollisionFlags).</returns>
	virtual int GetCollisionFlags() = 0;

	/// <summary>
	/// Toggle plugin events for OnPreCast when this spell is cast.
	/// </summary>
	/// <param name="TriggerEvents">if set to <c>true</c> [trigger plugin events].</param>
	virtual void SetTriggerEvents(bool TriggerEvents) = 0;

	/// <summary>
	/// Determines whether [is triggering plugin events].
	/// </summary>
	/// <returns>
	///   <c>true</c> if [is triggering plugin events]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsTriggeringEvents() = 0;

	/// <summary>
	/// Sets the name of the spell, not used for anything internally.
	/// </summary>
	/// <param name="SpellName">Name of the spell.</param>
	virtual void SetSpellName(std::string const& SpellName) = 0;

	/// <summary>
	/// Gets the name of the spell if set via SetSpellName.
	/// </summary>
	/// <returns>Spell name.</returns>
	virtual std::string GetSpellName() = 0;

	/// <summary>
	/// Sets the name of the charged buff to be used as a more reliable check for IsCharging.
	/// If only using DeltaTime then it will consider the charge done as soon as you reach max range.
	/// </summary>
	/// <param name="BuffName">Name of the buff.</param>
	virtual void SetChargedBuffName(std::string const& BuffName) = 0;

	/// <summary>
	/// Gets the name of the charged spell buff.
	/// </summary>
	/// <returns>Name of charged buff.</returns>
	virtual std::string GetChargedBuffName() = 0;
};

/// <summary>
/// Interface to interact with the core orbwalker.
/// </summary>
class IOrbwalking
{
public:
	/// <summary>
	/// Forces the orbwalker to attack the specified target, nullptr to erase it.
	/// </summary>
	/// <param name="Target">The target.</param>
	virtual void SetOverrideTarget(IUnit* Target) = 0;

	/// <summary>
	/// Forces the orbwalker to move to the specified position, Vec3(0, 0, 0) to erase it.
	/// </summary>
	/// <param name="Position">The position.</param>
	virtual void SetOverridePosition(Vec3 const& Position) = 0;

	/// <summary>
	/// Blocks the next attack from the orbwalker, meant for use in events such as OnOrbwalkPreAttack.
	/// </summary>
	virtual void DisableNextAttack() = 0;

	/// <summary>
	/// Toggle orbwalker movement.
	/// </summary>
	/// <param name="Enabled">if set to <c>true</c> [enabled].</param>
	virtual void SetMovementAllowed(bool Enabled) = 0;

	/// <summary>
	/// Toggle orbwalker attacks.
	/// </summary>
	/// <param name="Enabled">if set to <c>true</c> [enabled].</param>
	virtual void SetAttacksAllowed(bool Enabled) = 0;

	/// <summary>
	/// Gets the last target found.
	/// </summary>
	/// <returns>Last target.</returns>
	virtual IUnit* GetLastTarget() = 0;

	/// <summary>
	/// Gets the last position moved to.
	/// </summary>
	/// <returns>Last position.</returns>
	virtual Vec3 GetLastPosition() = 0;

	/// <summary>
	/// Gets the orbwalking mode.
	/// </summary>
	/// <returns>Orbwalking mode (eOrbwalkingMode).</returns>
	virtual eOrbwalkingMode GetOrbwalkingMode() = 0;

	/// <summary>
	/// Determines whether your player can currently attack.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance can attack; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CanAttack() = 0;

	/// <summary>
	/// Determines whether your player can move after the specified delay.
	/// </summary>
	/// <param name="Delay">The delay in seconds.</param>
	/// <returns>
	///   <c>true</c> if this instance can move after the specified delay; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CanMove(float Delay = 0.f) = 0;

	/// <summary>
	/// Resets attack timer.
	/// </summary>
	virtual void ResetAA() = 0;

	/// <summary>
	/// Gets the attack range to a specified target.
	/// </summary>
	/// <param name="Target">The target.</param>
	/// <returns>Attack range.</returns>
	virtual float GetAutoAttackRange(IUnit* Target) = 0;

	/// <summary>
	/// Orbwalks towards the specified position on the specified target.
	/// </summary>
	/// <param name="Target">The target.</param>
	/// <param name="Position">The position.</param>
	virtual void Orbwalk(IUnit* Target, Vec3 const& Position) = 0;
};

/// <summary>
/// Interface to access an item.
/// Use SetItemId and SetRange to convert to a new item.
/// </summary>
class IInventoryItem
{
public:
	/// <summary>
	/// Determines whether this instance is owned.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is owned; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsOwned() = 0;

	/// <summary>
	/// Determines whether this instance is ready.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is ready; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsReady() = 0;

	/// <summary>
	/// Gets the stacks.
	/// </summary>
	/// <returns>Item stacks.</returns>
	virtual int Stacks() = 0;

	/// <summary>
	/// Gets the charges.
	/// </summary>
	/// <returns>Item charges.</returns>
	virtual int Charges() = 0;

	/// <summary>
	/// Gets the name.
	/// </summary>
	/// <returns>Item name.</returns>
	virtual const char* GetName() = 0;

	/// <summary>
	/// Gets the display name.
	/// </summary>
	/// <returns>Required display name.</returns>
	virtual const char* DisplayName() = 0;

	/// <summary>
	/// Gets the name of the required spell.
	/// </summary>
	/// <returns>Required spell name.</returns>
	virtual const char* RequiredSpellName() = 0;

	/// <summary>
	/// Gets the required champion.
	/// </summary>
	/// <returns>Required champion name.</returns>
	virtual const char* RequiredChampion() = 0;

	/// <summary>
	/// Gets the item required level.
	/// </summary>
	/// <returns>Item required level.</returns>
	virtual int RequiredLevel() = 0;

	/// <summary>
	/// Gets the item ID.
	/// </summary>
	/// <returns>Item ID.</returns>
	virtual int ItemId() = 0;

	/// <summary>
	/// Gets the item spell slot.
	/// </summary>
	/// <returns>Item spell slot.</returns>
	virtual int ItemSpellSlot() = 0;

	/// <summary>
	/// Gets the maximum price for this item.
	/// </summary>
	/// <returns>Item max stacks.</returns>
	virtual int MaxStack() = 0;

	/// <summary>
	/// Gets the price for this item.
	/// </summary>
	/// <returns>Item price.</returns>
	virtual int Price() = 0;

	/// <summary>
	/// Determines if this item has been consumed.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this item [has been consumed]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool Consumed() = 0;

	/// <summary>
	/// Determines if this item is usable in store.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this item is [usable in store]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool UsableInStore() = 0;

	/// <summary>
	/// Determines if this item is consumed on acquiring.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this item is [consumed on acquire]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool ConsumeOnAcquire() = 0;

	/// <summary>
	/// Checks if the item can be clicked.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this item [is clickable]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool Clickable() = 0;

	/// <summary>
	/// Determines whether this item is [shown in active item display].
	/// </summary>
	/// <returns>
	///   <c>true</c> if this item is [shown in active item display]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool ShowInActiveItemDisplay() = 0;

	/// <summary>
	/// Determines whether this item [can be sold].
	/// </summary>
	/// <returns>
	///   <c>true</c> if this item [can be sold]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CanBeSold() = 0;

	/// <summary>
	/// Gets the sell back modifier as a percentage (0-1).
	/// </summary>
	/// <returns>Sell back modifier.</returns>
	virtual float SellBackModifier() = 0;

	/// <summary>
	/// Is item in the store.
	/// </summary>
	/// <returns>
	///   <c>true</c> if [item is in store]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool InStore() = 0;

	/// <summary>
	/// Casts on self.
	/// </summary>
	/// <returns>
	///   <c>true</c> if [cast was successful]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CastOnPlayer() = 0;

	/// <summary>
	/// Casts the on target.
	/// </summary>
	/// <param name="Target">The target.</param>
	/// <returns>
	///   <c>true</c> if [cast was successful]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CastOnTarget(IUnit* Target) = 0;

	/// <summary>
	/// Casts the on position.
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <returns>
	///   <c>true</c> if [cast was successful]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool CastOnPosition(Vec3 const& Position) = 0;

	/// <summary>
	/// Determines whether [is target in range] [the specified target].
	/// </summary>
	/// <param name="Target">The target.</param>
	/// <returns>
	///   <c>true</c> if [is target in range] [the specified target]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsTargetInRange(IUnit* Target) = 0;

	/// <summary>
	/// Determines whether [is point in range] [the specified position].
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <returns>
	///   <c>true</c> if [is point in range] [the specified position]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsPointInRange(Vec3 const& Position) = 0;

	/// <summary>
	/// Sets the range.
	/// </summary>
	/// <param name="Range">The range.</param>
	virtual void SetRange(float Range) = 0;

	/// <summary>
	/// Sets the item identifier.
	/// </summary>
	/// <param name="Id">The identifier.</param>
	virtual void SetItemId(int Id) = 0;
};

/// <summary>
/// Gets extended information about a spell given its data.
/// Data is passed in certain events such as OnProcessSpell (CastedSpell::Data).
/// </summary>
class ISpellData
{
public:
	/// <summary>
	/// Gets the caster.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Caster unit.</returns>
	virtual IUnit* GetCaster(void* Data) = 0;

	/// <summary>
	/// Gets the target, if applicable.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Target unit.</returns>
	virtual IUnit* GetTarget(void* Data) = 0;

	/// <summary>
	/// Determines whether [is automatic attack] [the specified data].
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>
	///   <c>true</c> if [is automatic attack] [the specified data]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsAutoAttack(void* Data) = 0;

	/// <summary>
	/// Gets the number of targets.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Number of targets.</returns>
	virtual int NumberOfTargets(void* Data) = 0;

	/// <summary>
	/// Gets the name of the spell.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Spell name.</returns>
	virtual const char* GetSpellName(void* Data) = 0;

	/// <summary>
	/// Gets the animation delay.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Animation time.</returns>
	virtual float GetAnimationDelay(void* Data) = 0;

	/// <summary>
	/// Gets the windup time.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Windup time.</returns>
	virtual float GetWindupTime(void* Data) = 0;

	/// <summary>
	/// Gets the start position.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Start position.</returns>
	virtual Vec3 GetStartPosition(void* Data) = 0;

	/// <summary>
	/// Gets the end position.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>End position.</returns>
	virtual Vec3 GetEndPosition(void* Data) = 0;

	/// <summary>
	/// Casts the cone angle.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Cone angle.</returns>
	virtual float CastConeAngle(void* Data) = 0;

	/// <summary>
	/// Gets the mana cost.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Mana cost.</returns>
	virtual float ManaCost(void* Data) = 0;

	/// <summary>
	/// Gets the radius.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Radius.</returns>
	virtual float GetRadius(void* Data) = 0;

	/// <summary>
	/// Gets the speed.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Speed.</returns>
	virtual float GetSpeed(void* Data) = 0;

	/// <summary>
	/// Gets the base damage.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Damage.</returns>
	virtual float GetBaseDamage(void* Data) = 0;

	/// <summary>
	/// Gets the range.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Range.</returns>
	virtual float GetRange(void* Data) = 0;

	/// <summary>
	/// Casts the target additional units radius.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Targets additional units radius.</returns>
	virtual float CastTargetAdditionalUnitsRadius(void* Data) = 0;

	/// <summary>
	/// Gets the spell cast time.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Spell cast time.</returns>
	virtual float SpellCastTime(void* Data) = 0;

	/// <summary>
	/// Gets the level.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Level.</returns>
	virtual int GetLevel(void* Data) = 0;

	/// <summary>
	/// Gets the slot.
	/// </summary>
	/// <param name="Data">The data.</param>
	/// <returns>Slot (eSpellSlot).</returns>
	virtual int GetSlot(void* Data) = 0;
};

/// <summary>
/// Gets extended information about spells (IUnit::GetSpellBook).
/// </summary>
class ISpellBook
{
public:
	/// <summary>
	/// Determines whether unit is charging a spell.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this unit is charging; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsCharging() = 0;

	/// <summary>
	/// Determines whether this unit is channeling.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this unit is channeling; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsChanneling() = 0;

	/// <summary>
	/// Gets the cast end time for this unit, if applicable.
	/// </summary>
	/// <returns>Cast end time.</returns>
	virtual float GetCastEndTime() = 0;

	/// <summary>
	/// Gets the spell state.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Spell state (eSpellState).</returns>
	virtual int GetSpellState(int Slot) = 0;

	/// <summary>
	/// Determines whether [is valid spell] [the specified slot].
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>
	///   <c>true</c> if [is valid spell] [the specified slot]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsValidSpell(int Slot) = 0;

	/// <summary>
	/// Gets the next cast time.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Next cast time.</returns>
	virtual float GetNextCastTime(int Slot) = 0;

	/// <summary>
	/// Gets the level.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Level.</returns>
	virtual int GetLevel(int Slot) = 0;

	/// <summary>
	/// Gets the total cooldown.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Total cooldown.</returns>
	virtual float GetTotalCooldown(int Slot) = 0;

	/// <summary>
	/// Gets the cast cone angle.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Cone angle.</returns>
	virtual float GetCastConeAngle(int Slot) = 0;

	/// <summary>
	/// Gets the mana cost.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Mana cost.</returns>
	virtual float GetManaCost(int Slot) = 0;

	/// <summary>
	/// Gets the radius.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Radius.</returns>
	virtual float GetRadius(int Slot) = 0;

	/// <summary>
	/// Gets the speed.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Speed.</returns>
	virtual float GetSpeed(int Slot) = 0;

	/// <summary>
	/// Gets the name.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Name.</returns>
	virtual const char* GetName(int Slot) = 0;

	/// <summary>
	/// Gets the base damage.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Damage.</returns>
	virtual float GetBaseDamage(int Slot) = 0;

	/// <summary>
	/// Gets the range.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Range.</returns>
	virtual float GetRange(int Slot) = 0;

	/// <summary>
	/// Gets the spell cast time.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Spell cast time.</returns>
	virtual float GetSpellCastTime(int Slot) = 0;

	/// <summary>
	/// Gets the state of the toggle.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Toggle state.</returns>
	virtual int GetToggleState(int Slot) = 0;

	/// <summary>
	/// Gets the cast time.
	/// </summary>
	/// <returns>Cast time.</returns>
	virtual float GetCastTime() = 0;

	/// <summary>
	/// Gets the ammo.
	/// </summary>
	/// <param name="Slot">The slot.</param>
	/// <returns>Ammo.</returns>
	virtual int GetAmmo(int Slot) = 0;
};

/// <summary>
/// Gets extended information about buffs (IUnit::GetAllBuffsData, IUnit::GetBuffDataByName, IUnit::GetBuffDataByIndex, etc.)
/// </summary>
class IBuffData
{
public:
	/// <summary>
	/// Returns true if buff is valid.
	/// </summary>
	/// <param name="BuffData">The buff data.</param>
	/// <returns>
	///   <c>true</c> if the specified buff data is valid; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsValid(void* BuffData) = 0;

	/// <summary>
	/// Gets the stacks.
	/// </summary>
	/// <param name="BuffData">The buff data.</param>
	/// <returns>Buff stacks.</returns>
	virtual int GetStacks(void* BuffData) = 0;

	/// <summary>
	/// Gets the caster.
	/// </summary>
	/// <param name="BuffData">The buff data.</param>
	/// <returns>Buff caster unit.</returns>
	virtual IUnit* GetCaster(void* BuffData) = 0;

	/// <summary>
	/// Gets the name of the source.
	/// </summary>
	/// <param name="BuffData">The buff data.</param>
	/// <returns>Source name.</returns>
	virtual const char* GetSourceName(void* BuffData) = 0;

	/// <summary>
	/// Gets the name of the buff.
	/// </summary>
	/// <param name="BuffData">The buff data.</param>
	/// <returns>Name.</returns>
	virtual const char* GetBuffName(void* BuffData) = 0;

	/// <summary>
	/// Gets the start time.
	/// </summary>
	/// <param name="BuffData">The buff data.</param>
	/// <returns>Start time.</returns>
	virtual float GetStartTime(void* BuffData) = 0;

	/// <summary>
	/// Gets the end time.
	/// </summary>
	/// <param name="BuffData">The buff data.</param>
	/// <returns>End time.</returns>
	virtual float GetEndTime(void* BuffData) = 0;

	/// <summary>
	/// Determines whether the specified buff data is active.
	/// </summary>
	/// <param name="BuffData">The buff data.</param>
	/// <returns>
	///   <c>true</c> if the specified buff data is active; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsActive(void* BuffData) = 0;

	/// <summary>
	/// Gets the type of the buff.
	/// </summary>
	/// <param name="BuffData">The buff data.</param>
	/// <returns>Type.</returns>
	virtual eBuffType GetBuffType(void* BuffData) = 0;
};

/// <summary>
/// Gets extended information about missile units (IUnit::IsMissile).
/// </summary>
class IMissileData
{
public:
	/// <summary>
	/// Gets the spell slot.
	/// </summary>
	/// <param name="MissileUnit">The missile unit.</param>
	/// <returns>Spell slot.</returns>
	virtual int GetSpellSlot(IUnit* MissileUnit) = 0;

	/// <summary>
	/// Gets the caster.
	/// </summary>
	/// <param name="MissileUnit">The missile unit.</param>
	/// <returns>Caster unit.</returns>
	virtual IUnit* GetCaster(IUnit* MissileUnit) = 0;

	/// <summary>
	/// Gets the target.
	/// </summary>
	/// <param name="MissileUnit">The missile unit.</param>
	/// <returns>Target unit, if applicable.</returns>
	virtual IUnit* GetTarget(IUnit* MissileUnit) = 0;

	/// <summary>
	/// Gets the end position.
	/// </summary>
	/// <param name="MissileUnit">The missile unit.</param>
	/// <returns>End cast position.</returns>
	virtual Vec3 GetEndPosition(IUnit* MissileUnit) = 0;

	/// <summary>
	/// Gets the start position.
	/// </summary>
	/// <param name="MissileUnit">The missile unit.</param>
	/// <returns>Start cast position.</returns>
	virtual Vec3 GetStartPosition(IUnit* MissileUnit) = 0;

	/// <summary>
	/// Gets the cast cone angle.
	/// </summary>
	/// <param name="MissileUnit">The missile unit.</param>
	/// <returns>Cast cone angle.</returns>
	virtual float GetCastConeAngle(IUnit* MissileUnit) = 0;

	/// <summary>
	/// Gets the radius.
	/// </summary>
	/// <param name="MissileUnit">The missile unit.</param>
	/// <returns>Missile radius.</returns>
	virtual float GetRadius(IUnit* MissileUnit) = 0;

	/// <summary>
	/// Gets the speed.
	/// </summary>
	/// <param name="MissileUnit">The missile unit.</param>
	/// <returns>Missile speed.</returns>
	virtual float GetSpeed(IUnit* MissileUnit) = 0;

	/// <summary>
	/// Gets the name.
	/// </summary>
	/// <param name="MissileUnit">The missile unit.</param>
	/// <returns>Missile name.</returns>
	virtual const char* GetName(IUnit* MissileUnit) = 0;

	/// <summary>
	/// Gets the base damage.
	/// </summary>
	/// <param name="MissileUnit">The missile unit.</param>
	/// <returns>Damage.</returns>
	virtual float GetBaseDamage(IUnit* MissileUnit) = 0;

	/// <summary>
	/// Gets the range.
	/// </summary>
	/// <param name="MissileUnit">The missile unit.</param>
	/// <returns>Range.</returns>
	virtual float GetRange(IUnit* MissileUnit) = 0;

	/// <summary>
	/// Gets the spell cast time.
	/// </summary>
	/// <param name="MissileUnit">The missile unit.</param>
	/// <returns>Cast time.</returns>
	virtual float GetSpellCastTime(IUnit* MissileUnit) = 0;

	/// <summary>
	/// Determines whether [is automatic attack] [the specified missile unit].
	/// </summary>
	/// <param name="MissileUnit">The missile unit.</param>
	/// <returns>
	///   <c>true</c> if [is automatic attack] [the specified missile unit]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsAutoAttack(IUnit* MissileUnit) = 0;
};

/// <summary>
/// Interface for interacting with the game engine navigation mesh.
/// </summary>
class INavMesh
{
public:
	/// <summary>
	/// Tests the line of sight to determine if there are any collisions.
	/// Collision position and flags are set if a collision is hit and it returns false.
	/// </summary>
	/// <param name="StartPosition">The start position.</param>
	/// <param name="EndPosition">The end position.</param>
	/// <param name="CollisionPositionOut">The collision position out.</param>
	/// <param name="CollisionFlagsOut">The collision flags out.</param>
	///   <c>true</c> if no collisions; otherwise, <c>false</c>.
	virtual bool TestLineOfSight(Vec3 const& StartPosition, Vec3 const& EndPosition, Vec3& CollisionPositionOut, int& CollisionFlagsOut) = 0;

	/// <summary>
	/// Gets the collision flags for a specified point.
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <returns>Collision flags (eMeshType).</returns>
	virtual int GetCollisionFlagsForPoint(Vec3 const& Position) = 0;

	/// <summary>
	/// Determines whether [is point wall] [the specified position].
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <returns>
	///   <c>true</c> if [is point wall] [the specified position]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsPointWall(Vec3 const& Position) = 0;

	/// <summary>
	/// Determines whether [is point grass] [the specified position].
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <returns>
	///   <c>true</c> if [is point grass] [the specified position]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsPointGrass(Vec3 const& Position) = 0;

	/// <summary>
	/// Gets the height for point.
	/// </summary>
	/// <param name="Position">The position.</param>
	/// <returns>World height for 2D point.</returns>
	virtual float GetHeightForPoint(Vec2 const& Position) = 0;
};

class IUtility
{
public:
	/// <summary>
	/// Determines whether [is league window focused].
	/// </summary>
	/// <returns>
	///   <c>true</c> if [is league window is focused]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsLeagueWindowFocused() = 0;

	/// <summary>
	/// Determines whether [is position in fountain] [the specified position].
	/// </summary>
	/// <param name="Source">The source position.</param>
	/// <param name="CheckTeamFountain">if set to <c>true</c> [check team fountain].</param>
	/// <param name="CheckEnemyFountain">if set to <c>true</c> [check enemy fountain].</param>
	/// <returns>
	///   <c>true</c> if [is position in fountain] [the specified position]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsPositionInFountain(Vec3 const& Source, bool CheckTeamFountain = true, bool CheckEnemyFountain = false) = 0;

	/// <summary>
	/// Determines whether [is position under turret] [the specified position].
	/// </summary>
	/// <param name="Source">The source position.</param>
	/// <param name="CheckTeamTurrets">if set to <c>true</c> [check team turrets].</param>
	/// <param name="CheckEnemyTurrets">if set to <c>true</c> [check enemy turrets].</param>
	/// <returns>
	///   <c>true</c> if [is position under turret] [the specified position]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsPositionUnderTurret(Vec3 const& Source, bool CheckTeamTurrets = false, bool CheckEnemyTurrets = true) = 0;

	/// <summary>
	/// Creates the debug console.
	/// </summary>
	virtual void CreateDebugConsole() = 0;

	/// <summary>
	/// Destroys the debug console.
	/// </summary>
	virtual void DestroyDebugConsole() = 0;

	/// <summary>
	/// Logs formatted text into the console.
	/// </summary>
	/// <param name="Fmt">The formatted text.</param>
	/// <param name="...">The additional arguments.</param>
	virtual void LogConsole(const char* Fmt, ...) = 0;

	/// <summary>
	/// Logs the formatted text to a file.
	/// </summary>
	/// <param name="Filename">The filename as stored in the "Logs" directory.</param>
	/// <param name="Fmt">The formatted text.</param>
	/// <param name="...">The additional arguments.</param>
	virtual void LogFile(const char* Filename, const char* Fmt, ...) = 0;

	/// <summary>
	/// Clears the log file.
	/// </summary>
	/// <param name="Filename">The filename as stored in the "Logs" directory.</param>
	virtual void ClearLogFile(const char* Filename) = 0;

	/// <summary>
	/// Converts a 2D world position to 3D.
	/// </summary>
	/// <param name="Other">The 2D world position.</param>
	/// <returns>3D worl position.</returns>
	virtual Vec3 To3D(Vec2 const& Other) = 0;

	/// <summary>
	/// Gets the experience required to reach a specified level.
	/// </summary>
	/// <param name="Level">The level to check.</param>
	/// <returns>Experience required.</returns>
	virtual float GetExperienceRequiredForLevel(int Level) = 0;

	/// <summary>
	/// Gets the duration of recall based on spell name.
	/// </summary>
	/// <param name="RecallSpellName">Name of the recall spell.</param>
	/// <returns>Recall duration.</returns>
	virtual int GetRecallDuration(const char* RecallSpellName) = 0;
};

/// <summary>
/// Prediction plugins should inherit and define this class to override core prediction.
/// </summary>
class IPluginPredictionOverride
{
public:
	/// <summary>
	/// Runs in replacement of core prediction when active.
	/// Input should be read and Output handled appropriately from the plugin.
	/// </summary>
	/// <param name="Input">The input.</param>
	/// <param name="Output">The output.</param>
	/// <param name="PredictionVersion">The prediction version, which determines the Input & Output structure.</param>
	virtual bool RunPrediction(AdvPredictionInput* Input, AdvPredictionOutput* Output, uint32_t PredictionVersion = 1) = 0;
};

/// <summary>
/// Main SDK interface to access all others.
/// </summary>
class IPluginSDK
{
public:
	/// <summary>
	/// Gets the orbwalking interface.
	/// </summary>
	/// <returns>IOrbwalking</returns>
	virtual IOrbwalking* GetOrbwalking() = 0;

	/// <summary>
	/// Gets the event manager interface.
	/// </summary>
	/// <returns>IEventManager</returns>
	virtual IEventManager* GetEventManager() = 0;

	/// <summary>
	/// Gets the renderer interface.
	/// </summary>
	/// <returns>IRender</returns>
	virtual IRender* GetRenderer() = 0;

	/// <summary>
	/// Gets the entity list interface.
	/// </summary>
	/// <returns>IEntityList</returns>
	virtual IEntityList* GetEntityList() = 0;

	/// <summary>
	/// Gets the game interface.
	/// </summary>
	/// <returns>IGame</returns>
	virtual IGame* GetGame() = 0;

	/// <summary>
	/// Gets the damage interface.
	/// </summary>
	/// <returns>IDamage</returns>
	virtual IDamage* GetDamage() = 0;

	/// <summary>
	/// Gets the prediction interface.
	/// </summary>
	/// <returns>IPrediction</returns>
	virtual IPrediction* GetPrediction() = 0;

	/// <summary>
	/// Gets the target selector interface.
	/// </summary>
	/// <returns>ITargetSelector</returns>
	virtual ITargetSelector* GetTargetSelector() = 0;

	/// <summary>
	/// Adds a new menu parent to the core menu.
	/// </summary>
	/// <param name="MenuTitle">The menu title.</param>
	/// <returns>IMenu</returns>
	virtual IMenu* AddMenu(const char* MenuTitle) = 0;

	/// <summary>
	/// Gets the health prediction interface.
	/// </summary>
	/// <returns>IHealthPrediction</returns>
	virtual IHealthPrediction* GetHealthPrediction() = 0;

	/// <summary>
	/// This has been deprecated, use ISpell2 instead.
	/// Creates a new ISpell interface.
	/// </summary>
	/// <param name="Slot">The spell slot (see eSpellSlot).</param>
	/// <param name="Range">The spell range.</param>
	/// <returns>ISpell</returns>
	virtual ISpell* CreateSpell(eSpellSlot Slot, float Range = FLT_MAX) = 0;

	/// <summary>
	/// Creates a data buffer from the URL page.
	/// </summary>
	/// <param name="Url">The URL to read.</param>
	/// <param name="Out">The output data.</param>
	/// <returns>True if URL was read successfully.</returns>
	virtual bool ReadFileFromURL(std::string const& Url, std::string& Out) = 0;

	/// <summary>
	/// Gets the base directory of L++.
	/// </summary>
	/// <param name="Out">The out.</param>
	virtual void GetBaseDirectory(std::string& Out) = 0;

	/// <summary>
	/// Creates an interface for handling spells.
	/// </summary>
	/// <param name="Slot">The spell slot (see eSpellSlot).</param>
	/// <param name="Type">The spell cast type - used for prediction.</param>
	/// <param name="IsMissile">if set to <c>true</c> [is missile] - used for prediction.</param>
	/// <param name="IsAoE">if set to <c>true</c> [is area of effect] - used for prediction.</param>
	/// <param name="CollisionFlags">The collision flags (see eCollisionFlags) - used for prediction. You should OR these flags as necessary (e.g kCollidesWithMinions|kCollidesWithYasuoWall).</param>
	/// <returns>ISpell2</returns>
	virtual ISpell2* CreateSpell2(eSpellSlot Slot, eSpellType Type, bool IsMissile, bool IsAoE, int/*eCollisionFlags*/ CollisionFlags) = 0;

	/// <summary>
	/// Creates an interface for handling items.
	/// </summary>
	/// <param name="ItemId">The item identifier.</param>
	/// <param name="Range">The item range.</param>
	/// <returns>IInventoryItem</returns>
	virtual IInventoryItem* CreateItemForId(int ItemId, float Range) = 0;

	/// <summary>
	/// Gets an interface to read further information from spell data passed in the CastedSpell::Data_ parameter of various events.
	/// </summary>
	/// <returns>ISpellData</returns>
	virtual ISpellData* GetSpellDataReader() = 0;

	/// <summary>
	/// Gets an interface to read further information from buff data found in functions such as IUnit::GetAllBuffs.
	/// </summary>
	/// <returns>IBuffData</returns>
	virtual IBuffData* GetBuffDataReader() = 0;

	/// <summary>
	/// Gets an interface to read further information from a missile IUnit (e.g pUnit->IsMissile()).
	/// </summary>
	/// <returns>IMissileData</returns>
	virtual IMissileData* GetMissileDataReader() = 0;

	/// <summary>
	/// Gets the IDirect3DDevice9 pointer.
	/// </summary>
	/// <returns>IDirect3DDevice9</returns>
	virtual PVOID GetIDirect3DDevice9Pointer() = 0;

	/// <summary>
	/// Calls a function after a set period of time.
	/// </summary>
	/// <param name="Milliseconds">The milliseconds before function is called.</param>
	/// <param name="Callback">The function to call.</param>
	virtual void DelayFunctionCall(int Milliseconds, std::function<void()> Callback) = 0;

	/// <summary>
	/// Registers a plugin interface that other plugins can access.
	/// </summary>
	/// <param name="Name">The name of the interface, should be a unique identifier.</param>
	/// <param name="Interface">The interface you are exposing.</param>
	virtual void RegisterPluginInterface(std::string const& Name, PVOID Interface) = 0;

	/// <summary>
	/// Removes a plugin interface from the internal list, can no longer be accessed from other plugins that haven't already accessed it.
	/// </summary>
	/// <param name="Name">The name.</param>
	virtual void UnRegisterPluginInterface(std::string const& Name) = 0;

	/// <summary>
	/// Finds a plugin interface.
	/// </summary>
	/// <param name="Name">The unique identifier for the interface that was registered with RegisterPluginInterface.</param>
	/// <returns>The interface that has been registered or nullptr if it doesn't exist.</returns>
	virtual PVOID FindPluginInterface(std::string const& Name) = 0;

	/// <summary>
	/// Gets the navmesh interface.
	/// </summary>
	/// <returns>INavMesh</returns>
	virtual INavMesh* GetNavMesh() = 0;

	/// <summary>
	/// Gets the utility interface.
	/// </summary>
	/// <returns>IUtility</returns>
	virtual IUtility* GetUtility() = 0;

	/// <summary>
	/// Registers a new prediction that will override core prediction
	/// </summary>
	/// <param name="PredictionTitle">The name as it will appear in the prediction options menu.</param>
	/// <param name="PluginPred">The plugin prediction interface.</param>
	virtual bool RegisterPredictionOverride(std::string const& PredictionTitle, IPluginPredictionOverride* PluginPred) = 0;

	/// <summary>
	/// Removes prediction override and reverts back to core prediction.
	/// </summary>
	/// <param name="PluginPred">The plugin prediction interface.</param>
	virtual void UnregisterPredictionOverride(IPluginPredictionOverride* PluginPred) = 0;
};

extern IPluginSDK*			GPluginSDK;
extern IEventManager*		GEventManager;
extern IRender*				GRender;
extern IEntityList*			GEntityList;
extern IGame*				GGame;
extern IDamage*				GDamage;
extern IPrediction*			GPrediction;
extern IHealthPrediction*	GHealthPrediction;
extern ITargetSelector*		GTargetSelector;
extern IOrbwalking*			GOrbwalking;
extern ISpellData* 			GSpellData;
extern IBuffData* 			GBuffData;
extern IMissileData* 		GMissileData;
extern INavMesh* 			GNavMesh;
extern IUtility*			GUtility;

#endif // PluginSDK_h__