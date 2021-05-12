// Russ 'trdwll' Treadwell <trdwll.com> - 2021

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "UObject/NoExportTypes.h"

#include <cryptolens/Configuration_Windows.hpp>
#include <cryptolens/Error.hpp>
#include <cryptolens/MachineCodeComputer_static.hpp>
#include <cryptolens/core.hpp>

#include "CryptolensUE.generated.h"

class FCryptolensUEModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
};

UENUM(BlueprintType)
enum class ELicenseFeature : uint8
{
	F1 UMETA(DisplayName = "Feature 1"),
	F2 UMETA(DisplayName = "Feature 2"),
	F3 UMETA(DisplayName = "Feature 3"),
	F4 UMETA(DisplayName = "Feature 4"),
	F5 UMETA(DisplayName = "Feature 5"),
	F6 UMETA(DisplayName = "Feature 6"),
	F7 UMETA(DisplayName = "Feature 7"),
	F8 UMETA(DisplayName = "Feature 8")
};

namespace cryptolens = ::cryptolens_io::v20190401;
using Cryptolens = cryptolens::basic_Cryptolens<cryptolens::Configuration_Windows<cryptolens::MachineCodeComputer_static>>;
using namespace cryptolens::errors;

UCLASS()
class CRYPTOLENSUE_API UCryptolens : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UCryptolens")
	static UCryptolensLicenseKey* GetLicenseKey(const FString& LicenseKey);

protected:
private:
};

// tbh I'd rather do this as a struct, but we can't expose methods to BP from structs
UCLASS()
class CRYPTOLENSUE_API UCryptolensLicenseKey : public UObject
{
	GENERATED_BODY()

public:
	UCryptolensLicenseKey() {}

	// custom helper methods

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	bool IsKeyExpired() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	bool DoesKeyHaveFeature(const ELicenseFeature Feature);

	// methods directly out of the library

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	int32 get_product_id() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	int32 get_period() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	int64 get_created() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	int64 get_expires() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	int64 get_sign_date() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	bool get_block() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	bool get_trial_activation() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	bool get_f1() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	bool get_f2() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	bool get_f3() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	bool get_f4() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	bool get_f5() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	bool get_f6() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	bool get_f7() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	bool get_f8() const;

	UFUNCTION(BlueprintCallable, Category = "CryptolensUE")
	FString ToString() const;

	cryptolens::optional<cryptolens::LicenseKey> GetLicenseKeyObj() const { return m_LicenseKey; }

	void Init(const FString& LicenseKey, Cryptolens& handle, cryptolens::Error& e);

protected:
private:
	// we really need C++17 support...
	cryptolens::optional<cryptolens::LicenseKey> m_LicenseKey;
};
