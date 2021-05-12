// Russ 'trdwll' Treadwell <trdwll.com> - 2021

#include "CryptolensUE.h"

#include "Core.h"
#include "Engine/Engine.h"
#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FCryptolensUEModule"

void FCryptolensUEModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("CryptolensUE")->GetBaseDir();
}

void FCryptolensUEModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCryptolensUEModule, CryptolensUE)

#pragma comment(lib, "winhttp.lib")

#define GETSTR(text, ...) *FString::Printf(TEXT(text), ##__VA_ARGS__)
#define PRINT(text, ...) \
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Purple, GETSTR(text, ##__VA_ARGS__))

UCryptolensLicenseKey* UCryptolens::GetLicenseKey(const FString& LicenseKey)
{
	if (UCryptolensLicenseKey* KeyObj = NewObject<UCryptolensLicenseKey>())
	{
		cryptolens::Error e;
		Cryptolens cryptolens_handle(e);

		// Setting up the signature verifier with credentials from "Security Settings" on serialkeymanager.com
		cryptolens_handle.signature_verifier.set_modulus_base64(e, "0qoNb36dLXFirsOz32a41AtZIvk4hfzeBvg5LRXngVwTxrlddeaoyWuPunBwqhAbasOfTGJ0E+naqr6wvPqt0ZnN/aalV/xUSG9/HW6KMSaoiwnuEjTrs0FWWKSwAfCEKuS7y2iwU4l5SOHa3MBv2c8Myav3n3lpueqMVVGlSNJSeyilhRFVBumts+hSjh5cI4EJ56RI57VtXgANtPAmI32CRxaj78sg8N8Do2bRnOed4MM7SbnWeqFd/IYbQwZuzlPBzlTbtu/DyGFjsZu2gxwSm5yjMGlgCE664xeloKGaP3W1/9g8RgfS9LsRyAMejWt2SGSX4KqF0LVCq6VTiw==");
		cryptolens_handle.signature_verifier.set_exponent_base64(e, "AQAB");
		cryptolens_handle.machine_code_computer.set_machine_code(e, "289jf2afs3");

		KeyObj->Init(LicenseKey, cryptolens_handle, e);

		if (e)
		{
			if (e.get_subsystem() == Subsystem::Main)
			{
				// Handle errors from the SKM API
				PRINT("SKM error %d", e.get_reason());
			}
			else if (e.get_subsystem() == Subsystem::RequestHandler)
			{
				size_t code = e.get_extra();
				PRINT("Error connecting to the server: error code: %d", code);
			}
			else
			{
				PRINT("Unhandled error: %d, %d, %d", e.get_subsystem(), e.get_reason(), e.get_extra());
			}
		}

		return KeyObj;
	}

	return nullptr;
}

bool UCryptolensLicenseKey::IsKeyExpired() const
{
	if (!m_LicenseKey)
	{
		return true;
	}

	// annoying cast, apparently the explicit bool operator isn't working...
	return (bool)m_LicenseKey->checkKey().has_expired(FDateTime::Now().ToUnixTimestamp());
}

bool UCryptolensLicenseKey::DoesKeyHaveFeature(const ELicenseFeature Feature)
{
	switch (Feature)
	{
	case ELicenseFeature::F1:
		return m_LicenseKey->get_f1() == 1;
	case ELicenseFeature::F2:
		return m_LicenseKey->get_f2() == 1;
	case ELicenseFeature::F3:
		return m_LicenseKey->get_f3() == 1;
	case ELicenseFeature::F4:
		return m_LicenseKey->get_f4() == 1;
	case ELicenseFeature::F5:
		return m_LicenseKey->get_f5() == 1;
	case ELicenseFeature::F6:
		return m_LicenseKey->get_f6() == 1;
	case ELicenseFeature::F7:
		return m_LicenseKey->get_f7() == 1;
	case ELicenseFeature::F8:
		return m_LicenseKey->get_f8() == 1;
	}

	return false;
}

int32 UCryptolensLicenseKey::get_product_id() const
{
	return m_LicenseKey->get_product_id();
}

int32 UCryptolensLicenseKey::get_period() const
{
	return m_LicenseKey->get_period();
}

int64 UCryptolensLicenseKey::get_created() const
{
	return m_LicenseKey->get_created();
}

int64 UCryptolensLicenseKey::get_expires() const
{
	return m_LicenseKey->get_expires();
}

int64 UCryptolensLicenseKey::get_sign_date() const
{
	return m_LicenseKey->get_sign_date();
}

bool UCryptolensLicenseKey::get_block() const
{
	return m_LicenseKey->get_block();
}

bool UCryptolensLicenseKey::get_trial_activation() const
{
	return m_LicenseKey->get_trial_activation();
}

bool UCryptolensLicenseKey::get_f1() const
{
	return m_LicenseKey->get_f1();
}

bool UCryptolensLicenseKey::get_f2() const
{
	return m_LicenseKey->get_f2();
}

bool UCryptolensLicenseKey::get_f3() const
{
	return m_LicenseKey->get_f3();
}

bool UCryptolensLicenseKey::get_f4() const
{
	return m_LicenseKey->get_f4();
}

bool UCryptolensLicenseKey::get_f5() const
{
	return m_LicenseKey->get_f5();
}

bool UCryptolensLicenseKey::get_f6() const
{
	return m_LicenseKey->get_f6();
}

bool UCryptolensLicenseKey::get_f7() const
{
	return m_LicenseKey->get_f7();
}

bool UCryptolensLicenseKey::get_f8() const
{
	return m_LicenseKey->get_f8();
}

FString UCryptolensLicenseKey::ToString() const
{
	return UTF8_TO_TCHAR(m_LicenseKey->to_string().c_str());
}

void UCryptolensLicenseKey::Init(const FString& LicenseKey, Cryptolens& handle, cryptolens::Error& e)
{
	m_LicenseKey = handle.activate(
		e,
		// SKM Access Token
		"WyIxMzQ2MTk4IiwicTNCWFAvUmFmMjBwRnlLUXFQNmtsQ1IrT1pFRUpSeFdHVDBKbHQxNiJd",
		// Product id
		10833,
		// License Key
		TCHAR_TO_UTF8(*LicenseKey));
}
