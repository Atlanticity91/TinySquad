/******************************************************************************************
 * 
 * @author   : ALVES Quentin
 * @creation : 19/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Game Production template for Tiny Engine usage.
 *
 ******************************************************************************************/

#include <TinyEngine/TinyGameEntry.h>

/**
 * TinyProduction class
 * @note : Production game class.
 **/
class TinyProduction final : public TinyGame {

public:
	/**
	 * Constructor
	 **/
	TinyProduction( );

	/**
	 * Destructor
	 **/
	~TinyProduction( ) = default;

protected:
	/**
	 * Initialize function
	 * @note : Optional override for custom init action.
	 * @return : Return True for success, if this function return false the
	 * 			 game will not start cause init failed.
	 **/
	virtual bool Initialize( ) override;

	/**
	 * SetupBundles method
	 * @note : Optional override for custom passes.
	 * @param graphics : Current graphic manager instance.
	 **/
	virtual void SetupBundles( TinyGraphicManager& graphics ) override;

	/**
	 * LoadInterop method
	 * @note : Optional override for register custom Lua-C++ interop.
	 * @param lua_context : Current game lua interop context instance.
	 **/
	virtual void LoadInterop( TinyLuaContext& lua_context ) override;

	/**
	 * LoadContent method
	 * @note : Optional override for loading assets at the begin of the game.
	 * @note : Current game asset manager instance.
	 **/
	virtual void LoadContent( TinyAssetManager& assets ) override;

	/**
	 * LoadECS method
	 * @note : Required override for defined default systems used by the ECS.
	 * @param : Current game ECS instance.
	 **/
	virtual void LoadECS( TinyECS& ecs ) override;

	/**
	 * Tick method
	 * @note : Optional override, game tick called once a frame between pre and post tick.
	 **/
	virtual void Tick( ) override;

	/**
	 * Terminate method
	 * @note : Optional override for custom termination and cleanup action.
	 **/
	virtual void Terminate( ) override;

};
