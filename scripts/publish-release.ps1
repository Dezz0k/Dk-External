# Publishes a GitHub Release with the built exe as DkExternal.exe
# Usage (from repo root):
#   .\scripts\publish-release.ps1 -Version 1.1.1

param(
    [Parameter(Mandatory = $true)]
    [string]$Version,

    [string]$ExePath = "",
    [string]$AssetName = "DkExternal.exe"
)

$ErrorActionPreference = "Stop"

if ($Version.StartsWith("v")) {
    $Tag = $Version
    $Version = $Version.Substring(1)
} else {
    $Tag = "v$Version"
}

if ([string]::IsNullOrWhiteSpace($ExePath)) {
    $ExePath = "x64\Release\Dk External v$Version.exe"
}

if (-not (Test-Path $ExePath)) {
    throw "Built exe not found: $ExePath  (build Release x64 first)"
}

$staging = Join-Path $env:TEMP $AssetName
Copy-Item -Force $ExePath $staging

Write-Host "Creating release $Tag with asset $AssetName..."
gh release create $Tag $staging --title "Dk External $Tag" --notes "Auto-update release $Tag" --latest

Write-Host "Done. Bump UpdaterConfig::APP_VERSION in inc/updater.hpp to `"$Version`" before the next build you ship."
